/**********************************************************
*						  	  *
*		       			Projet UNIX MAIN 		           *
*							  *
**********************************************************/
#include "CL_include"

static void end(); 
static int Msqid;
static int Shmid;
static int Semid_lecteurs;
static key_t CleClient;
void Handler_sig_memory(int); 
void* lecteur_task(int voie);
BUF *MemBuf;

/**
 * @brief Fonction principale du client
 * 
 * @return int 
 */
int main(int argc, char *argv[]){

	/* GESTION DES SIGNAUX */
	signal(SIGTERM, end);
  	signal(SIGINT, end);	

	/* GESTION DES SIGNAUX USR */
	signal(SIGUSR1, Handler_sig_memory);
	signal(SIGUSR2, Handler_sig_memory);
	
	Semid_lecteurs = Sem_create();
	
	pthread_t thread_lecteur0;
	pthread_create(&thread_lecteur0, NULL, lecteur_task, 0);
	
	pthread_t thread_lecteur1;
	pthread_create(&thread_lecteur1, NULL, lecteur_task, 1);
	
	
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

	/* BOUCLE */
	int i=0;
	while(i<nbdata){
		pause(); /* on attend un signal */
		i++;
	}
	sleep(0.2);
	kill(thread_lecteur0, SIGKILL); /* kill lecteur */
	kill(thread_lecteur1, SIGKILL); /* kill lecteur */
	return 0;
}
void* lecteur_task(int voie){
	main_lecteur(voie, Semid_lecteurs, &MemBuf);
	pthread_exit(NULL);
}

/**
 * @brief Handler de signal pour la memoire partagee
 * 
 * @param sig 
 */
void Handler_sig_memory(int sig){
	if(sig==SIGUSR1){
		printf("Signal SIGUSR1 recu\n");
		printf("pere libere ressource lecteur voie %d\n",0);
		V(Semid_lecteurs,0);
	}
	if(sig==SIGUSR2){
		printf("Signal SIGUSR2 recu\n");
		printf("pere libere ressource lecteur voie %d\n",1);
		V(Semid_lecteurs,1);
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

