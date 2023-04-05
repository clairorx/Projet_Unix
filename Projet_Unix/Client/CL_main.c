/**********************************************************
*						  	  *
*		       			Projet UNIX MAIN 		           *
*							  *
**********************************************************/
#include "CL_include"

static void end(); 
static int Msqid;
static int Shmid;
static int Semid_lecteur;
static int Semid_redacteur;
static key_t CleClient;
pid_t pidPere, pidLecteur0, pidLecteur1,pidRedacteur0,pidRedacteur1;
void Handler_sig_memory(int); 
void* lecteur_task(int voie);
BUF *MemBuf;
int pfd1[2]; 
int pfd0[2];

/**
 * @brief Fonction principale du client
 * 
 * @return int 
 */
int main(int argc, char *argv[]){
	pidPere = getpid();

	/* CREATION DU CONDUIT 0 */
    if (pipe(pfd0) == -1)
        printf("Erreur pipe\n");

	/* CREATION DU CONDUIT 1 */
    if (pipe(pfd1) == -1)
        printf("Erreur pipe\n");

	/* GESTION DES SIGNAUX */
	signal(SIGTERM, end);
  	signal(SIGINT, end);	

	/* CREATION DES SEMAPHORES */
	Semid_lecteur = Sem_create();
	Semid_redacteur = Sem_create();

	int nbdata=atoi(argv[1]);
  	if (nbdata <= 0){
      	printf("Erreur dans la valeur du parametre de sv_zz\n");
     	exit(0);
    }

	/* CREATION MESSAGERIE */
	printf("Test Client\n");
	Msqid = CreationMessagerie();
	printf("msqid = %d\n", Msqid);

	/* CONNEXION SERVEUR */
	CleClient = ConnectServeur(Msqid); 
	printf("Cle client = %d\n", CleClient);

	/* CREATION SHARED MEMORY */
	printf("\nObtention de l'ID de la mémoire partagée\n");
	Shmid = CreationSharedMemory(&MemBuf,CleClient);
	printf("Shmid = %d\n", Shmid);
	
	int limiteN = (MemBuf+0)->n + (MemBuf+1)->n + nbdata - 1;
	
	if((pidLecteur0=fork()) != 0){ /* Code du pere */
		if((pidLecteur1=fork()) != 0){ /* Code du pere */
			/* GESTION DES SIGNAUX USR */
			signal(SIGUSR1, Handler_sig_memory);
			signal(SIGUSR2, Handler_sig_memory);
			
			/* BOUCLE */
			int i=0;
			while(i<nbdata){
				pause(); /* on attend un signal */
				i++;
			}
		}
		else{ /* Code du lecteur 1 */
			if((pidRedacteur1=fork()) != 0){ /* Code du lecteur 1 */
				main_lecteur(1, Semid_redacteur, Semid_lecteur, &MemBuf, limiteN, pfd0);
				exit(0);
			}
			else{ /* Code du Redacteur 1 */
				main_redacteur(1, Semid_redacteur, pfd0, limiteN);
				exit(0);
			}
		}
	}
	else{ /* Code du lecteur 0 */
		if((pidRedacteur0=fork()) != 0){ /* Code du lecteur 0 */
				main_lecteur(0, Semid_redacteur, Semid_lecteur, &MemBuf, limiteN, pfd1);
				exit(0);
			}
			else{ /* Code du Redacteur 0 */
				main_redacteur(0, Semid_redacteur, pfd1, limiteN);
				exit(0);
			}
	}
	waitpid(pidLecteur0,NULL,0);
	waitpid(pidLecteur1,NULL,0);
	
	return 0; 
}

/**
 * @brief Handler de signal pour la memoire partagee
 * 
 * @param sig 
 */
void Handler_sig_memory(int sig){
	if(sig==SIGUSR1){
		/*printf("Signal SIGUSR1 recu\n");*/
		V(Semid_lecteur,0);
	}
	if(sig==SIGUSR2){
		/*printf("Signal SIGUSR2 recu\n");*/
		V(Semid_lecteur,1);
	}
}

/**
 * @brief Fonction de fin du client
 * 
 */
static void end() { 
  printf("\nSrv:FIN Mort du fils receptionniste \n");
  DeconnectServeur(Msqid);

  printf("\nSrv:FIN RelachMsg %d\n", RelacheMessagerie(Msqid));
  kill(0,SIGKILL); /* on tue tout le monde */
}

