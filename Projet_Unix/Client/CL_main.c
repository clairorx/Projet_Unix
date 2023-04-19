/**********************************************************
*						  	  *
*		       			Projet UNIX MAIN 		           *
*							  *
**********************************************************/
#include "CL_include"

/* DECLARATION VARIABLES GLOABLES */
static int Msqid;
static int Shmid;
static int Semid_lecteur;
static int Semid_driver;
static int voie_libre; 
static key_t CleClient;
pid_t pidPere, pidLecteur0, pidLecteur1,pidRedacteur0,pidRedacteur1,pidDriver;
void Handler_sig_memory(int); 
void* lecteur_task(int voie);
BUF *MemBuf;
int pfd1[2]; 
int pfd0[2];
int pfd_driver[2];

/**
 * @brief Fonction principale du client
 * 
 * @return int 
 */
int main(int argc, char *argv[]){
	pidPere = getpid();

	/* CREATION DU CONDUIT 0 */
    if (pipe(pfd0) == -1){
        printf("Erreur pipe\n");
	}
	
	/* CREATION DU CONDUIT 1 */
    if (pipe(pfd1) == -1){
        printf("Erreur pipe\n");	
	}

	/* CREATION DU PIPE DRIVER */
    if (pipe(pfd_driver) == -1){
        printf("Erreur pipe\n");	
	}

	/* CREATION DES SEMAPHORES */
	Semid_lecteur = Sem_create();
	Semid_driver = Sem_create();
	V(Semid_driver,0);

	
	int nbdata=atoi(argv[1]);
  	if (nbdata <= 0){
      	printf("Erreur dans la valeur du parametre de sv_zz\n");
     	exit(0);
    }

	/* CREATION MESSAGERIE */
	/*printf("Test Client\n");*/
	Msqid = CreationMessagerie();
	/*printf("msqid = %d\n", Msqid);*/

	/* CONNEXION SERVEUR */
	CleClient = ConnectServeur(Msqid); 
	printf("\nCle client = %d\n", CleClient);
	printf("\n*******************Connectée au serveur*******************\n");
	/* CREATION SHARED MEMORY */
	/*printf("\nObtention de l'ID de la mémoire partagée\n");*/
	Shmid = CreationSharedMemory(&MemBuf,CleClient);
	/*printf("Shmid = %d\n", Shmid);*/
	printf("\nPtr tampon = %p\n", MemBuf);
	printf("\n");

	printf("\nDebut de reception des données\n\n");
	
	
	if((pidLecteur0=fork()) != 0){ /* Code du pere */
		if((pidLecteur1=fork()) != 0){ /* Code du pere */
			if((pidRedacteur1=fork()) != 0){ /* Code du pere */
				if((pidRedacteur0=fork()) != 0){ /* Code du pere */
					if((pidDriver=fork()) !=0){ /* Code du pere */
						/* GESTION DES SIGNAUX */
						/*signal(SIGTERM, end);
						signal(SIGINT, end);
						signal(SIGKILL, end);*/
				
						/* GESTION DES SIGNAUX USR */
						signal(SIGUSR1, Handler_sig_memory);
						signal(SIGUSR2, Handler_sig_memory);
						
						/* BOUCLE */
						int i=0;
						while(i<nbdata){
							pause(); /* on attend un signal */
							V(Semid_lecteur,voie_libre);
							i++;
						}
					}
					else{ /* Code du driver */
						/* Redirection de l'enteée standard vers le pipe du driver */
						close(0); 
						dup(pfd_driver[0]);

						/* Appel du Driver executable */
						execlp("./Driver", "./Driver", NULL);
					}
				}
				else{ /* Code du Redacteur 0 */
					main_redacteur(0, Semid_driver, pfd1, pfd_driver);
				}
			}
			else{ /* Code du Redacteur 1 */
				main_redacteur(1, Semid_driver, pfd0, pfd_driver);
			}
		}
		else{ /* Code du lecteur 1 */
			main_lecteur(1, Semid_lecteur, &MemBuf, pfd0);
		}
	}
	else{ /* Code du lecteur 0 */
		main_lecteur(0, Semid_lecteur, &MemBuf, pfd1);
	}

	/* KILL PROCESSUS FILS */
	kill(pidLecteur0,SIGKILL);
	waitpid(pidLecteur0,NULL,0);
	/*printf("kill lecteur0");*/
	kill(pidLecteur1,SIGKILL);
	waitpid(pidLecteur1,NULL,0);
	/*printf("kill lecteur1");*/
	kill(pidRedacteur0,SIGKILL);
	waitpid(pidRedacteur0,NULL,0);
	/*printf("kill redacteur0");*/
	kill(pidRedacteur1,SIGKILL);
	waitpid(pidRedacteur1,NULL,0);
	/*printf("kill redacteur1");*/
	kill(pidDriver,SIGKILL);
	waitpid(pidDriver,NULL,0);
	/*printf("kill Driver");*/
	
	

	/* DECONNECTION SERVEUR */
	DeconnectServeur(Msqid);
	printf("\nClient:FIN RelachMsg %d\n", RelacheMessagerie(Msqid));
	printf("\nClient:FIN Mort du Client \n");
	
	/* DESTRUCTION DES SEMAPHORES */
	Sem_destroy(Semid_lecteur);
	Sem_destroy(Semid_driver);
	
	return 0; 
}

/**
 * @brief Handler de signal pour la memoire partagee
 * A modifier
 * @param sig 
 */
void Handler_sig_memory(int sig){
	if(sig==SIGUSR1){
		/*printf("Signal SIGUSR1 recu\n");*/
		voie_libre = 0;
	}
	if(sig==SIGUSR2){
		/*printf("Signal SIGUSR2 recu\n");*/
		voie_libre = 1;
	}
}


