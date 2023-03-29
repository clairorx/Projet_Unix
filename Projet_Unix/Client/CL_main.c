/**********************************************************
*						  	  *
*		       			Projet UNIX MAIN 		           *
*							  *
**********************************************************/
#include "CL_include"

static void end(); 
static int Msqid;
static int Shmid;
static key_t CleClient;
void Handler_sig_memory(int); 
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
	return 0;
}

/**
 * @brief Handler de signal pour la memoire partagee
 * 
 * @param sig 
 */
void Handler_sig_memory(int sig){
	if(sig==SIGUSR1){
		printf("Signal SIGUSR1 recu\n"); 
		read_data(0, &MemBuf);
	}
	if(sig==SIGUSR2){
		printf("Signal SIGUSR2 recu\n"); 
		read_data(1, &MemBuf);
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

