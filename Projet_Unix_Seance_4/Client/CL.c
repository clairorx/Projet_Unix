/********************************************************
*	Fichier CL.c				*
*-----------------------------------------------------------------------*
Margot Chaumette/ Léo Festoc/ Maxime Pieau
20/03/2023
************************************************************************/
/* fichier include */
#include "CL_include"


/*Fonctions*/
void my_handler(int n);
void my_handler2(int n);
void  AttacheSegment (int size, char *name);
void Lecteur(int Sem_lect, int num_voie,int *pfd,int Sem_Serv);
void P(SEMAPHORE sem, int NumSemaphore);
void V(SEMAPHORE sem, int NumSemaphore);
SEMAPHORE CreationMutex();
int DestructionMutex(SEMAPHORE semid);
void Detruire_sem(SEMAPHORE sem);
int Init_Mutex(int semid, int nb);
 SEMAPHORE Creer_sem(key_t cle, unsigned short *val_init);
void Changer_sem(SEMAPHORE sem, int val, int NumSemaphore);
void Redacteur (int numlect,int *pfd);
/*Variables*/
  
    /*Cles*/ /*Les clees doivent etres variable globales*/
    key_t key_messagerie;
    key_t CleClient;
    key_t Cle_Driver;
    /**/
    int num_voie;
    BUF *PtrMem;
    char cle_acces_mem[200];
    int pfd_driver[2];

int main(int argc,char *argv[])
{ 
    /*Declaration variables*/
    int  nbdata;
    /*Declaration PID*/
    int pid_client = getpid();
    int pid_lecteur_1=0,pid_lecteur_2=0;
    int pid_redacteur_1=0,pid_redacteur_2=0;
    int pid_driver=0;
    
    unsigned short val_init_moniteur[2]={0, 0};
    int  msqid;
    dmsgbuf message;
    int pfd1[2],pfd2[2];

    /*Création des conduits*/
    if(pipe(pfd1) == -1)
      printf("Erreur de création du pipe 1\n");
    if(pipe(pfd2) == -1)
      printf("Erreur de création du pipe 2\n");
    if(pipe(pfd_driver) == -1)
      printf("Erreur de création du pipe driver\n");
    
    /*Création sémaphore du client */
    SEMAPHORE Sem_lect= Creer_sem(IPC_PRIVATE,val_init_moniteur);
    /*Création/attachement sémaphore du serveur */
    SEMAPHORE Sem_serv = CreationMutex();
  
    /*TEST si le nombre d'argument est bon ( si on donne bien le nombre de secondes du lancement du client)*/
    if (argc < 2)
    {
      printf("\n!!!! Usage : CL  <+/-nombre de donnees>\n");
      exit(0);
    }
    nbdata=atoi(argv[1]);
    if (nbdata==0)
    {
      printf("\n NB DONNEES DIFFERENT DE 0\n");
      exit(0);
    }

	
  /*Affichage Debut */
          printf("\n* * * * * * * * * * * * * * * * *\n");
          printf("* \tClient en service \t*");
          printf("\n* * * * * * * * * * * * * * * * *\n");

  /*Creation de cle*/
  if (( key_messagerie = ftok(CleServeur,C_Msg)) < 0 )   /* cle messagerie*/
      return CLEerr;
  msqid = msgget(key_messagerie,0666);  /* identifiant messagerie*/
  printf("\nCl:ID messagerie Msqid = %d\n",msqid);
  

  /*Demande de Connexion a la messagerie*/
  message.type= CONNECT;
  sprintf(message.txt,"%d",pid_client);
  if (msgsnd(msqid,&message,strlen(message.txt)+1,0) <0){
    printf("erreur connection client\n");
  } else{
		printf("\n\tTEST:\tConnecte\n");	
	}
/*initialisation au sémaphore du serveur */
 if (Init_Mutex(Sem_serv, 1) == SEMerr)	/* Init du semaphore Mutex a 1 */
    {
      printf("CL:Destruction Mutex %d\n",DestructionMutex(Sem_serv));
      exit(0);
    }

    /*Reception d'un  message : reception de la clé*/
    message.type = pid_client;
		if (   (msgrcv(msqid,&message,L_MSG,message.type,0)) <0)
		  {
        printf("erreur reception Cle\n");
      }   
  else{
		printf("\n\tTEST:\tReception Cle  \n");	
	}
		printf("Srv:Reception MESSAGE:%s %ld\n",message.txt,message.type);
    strcpy(cle_acces_mem,message.txt);   /*cle de la memoire partage*/

  /*Envoie Acknoledgement pour savoir si on est bien connecté*/
	message.type= ACK;
	sprintf(message.txt,"%d",pid_client);
	if (msgsnd(msqid,&message,strlen(message.txt)+1,0) <0){
      printf("Erreur de confirmation du client ACK\n");
      return MSGerr;
  }else {
		printf("\n\tTEST:\t ACK\n");
	}

  /*Attachement à la mémoire*/
  AttacheSegment(2*sizeof(BUF),cle_acces_mem);
	
  /*Assignation des fonction handler aux signaux*/
  signal(SIGUSR1, my_handler);/* reception signal 1, passage num_voie =0 */
	signal(SIGUSR2, my_handler2);/* reception signal 2, passage num_voie =1 */

int i;
  /*On commence creer 5 fils, 2 lecteur, 2 rédcateur et 1 driver */
  /*Création fils lecteur 1*/
  pid_lecteur_1 = fork(); 
if (pid_lecteur_1 < 0) { 
  perror("Creer fils lecteur 1");
  exit(EXIT_FAILURE);
} else if (pid_lecteur_1 == 0) { /*Code du lecteur 1 */
  Lecteur(Sem_lect, 0,pfd1,Sem_serv); /*appel de la fonction lecteur 1 avec les sémaphore lecteur et serveur ainsi que le pipe du lecteur 1*/
} else {
  /*Création fils lecteur 2*/
  pid_lecteur_2 = fork();
  if (pid_lecteur_2 < 0) { 
    perror("Creer fils lecteur 2");
    exit(EXIT_FAILURE);
  } else if (pid_lecteur_2 == 0) { /*Code du lecteur 2 */
    Lecteur(Sem_lect, 1,pfd2,Sem_serv); /*appel de la fonction lecteur 2 avec les sémaphore lecteur et serveur ainsi que le pipe du lecteur 2*/
    exit(0);
  } else {
    /*Création fils rédacteur 1*/
    pid_redacteur_1 = fork();
    if (pid_redacteur_1 < 0) {
      perror("Creer fils redacteur 1");
      exit(EXIT_FAILURE);
    } else if (pid_redacteur_1 == 0) { /*Code du rédacteur 1 */
      Redacteur(0,pfd1); /*appel de la fonction rédacteur 1 avec le numéro de voie 0 ainsi que le pipe 1*/

      exit(0);
    } else {
      /*Création fils rédacteur 2*/
      pid_redacteur_2 = fork(); 
      if (pid_redacteur_2 < 0) {
        perror("Creer fils redacteur 2");
        exit(EXIT_FAILURE);
      } else if (pid_redacteur_2 == 0) { /*Code du rédacteur 2 */
        Redacteur(1,pfd2); /*appel de la fonction rédacteur 2 avec le numéro de voie 1 ainsi que le pipe 2*/
        exit(0);
      } else {
        /*Création fils driver */
        pid_driver = fork();
        if (pid_driver < 0) {
          perror("Creer fils driver");
          exit(EXIT_FAILURE);
        } else if (pid_driver == 0) { /*Code du driver */
          close(0); /*fermeture entrée standard */
        dup2(pfd_driver[0],STDIN_FILENO);  /*redirection de l'entrée standard vers le pipe driver */
        close(pfd_driver[1]);
        close(pfd_driver[0]);
      
        if(execlp("./DRIVER.exe","./DRIVER.exe",0)== -1) /* appel au programme driver*/
		    {
			    printf("Erreur CL_Driver");
          exit(0);
		    } 
        exit(0);
        } else {
          for(i =0;i<nbdata;i++){ /* boucle pour la lecture de toutes les données */
            pause();
            if(num_voie==0) V(Sem_lect,0); /* déblocage semaphore lecteur 0 */
            else V(Sem_lect,1); /* déblocage semaphore lecteur 1 */
          }
        }
      }
    }
  }
}
   
/*Destruction des fils */
printf("Mort des fils Client \n");
if(kill(pid_driver, SIGKILL) == -1)
    perror("clean : kill pid_driver");

if(kill(pid_redacteur_2, SIGKILL) == -1)
		perror("clean : kill pid_redacteur2");

if(kill(pid_redacteur_1, SIGKILL) == -1)
	perror("clean : kill pid_redacteur 1");

if(kill(pid_lecteur_2, SIGKILL) == -1)
	perror("clean : kill pid_lecteur2");

if(kill(pid_lecteur_1, SIGKILL) == -1)
		perror("clean : kill pid_lecteur1");

  /*Destruction des sémaphore*/
  printf("Destruction des sémaphore \n");
  Detruire_sem(Sem_lect);

  /*Detachement mémoire partagée*/
  printf("Détachement mémoire partagée\n");
  if(shmdt(PtrMem)==-1)
   	{
   	  	perror("detachement impossible PtrMem \n") ;
     		exit(1) ;
   	}
	printf("La mémoire partage est détachée\n") ;

  /* DECONNECTION	*/
	message.type= DECONNECT;
	sprintf(message.txt,"%d",pid_client );
	if (msgsnd(msqid,&message,strlen(message.txt)+1,0) <0)
	{
	  printf("\terreur dans client deconnect\n");
	}
	else
	{
	  printf("\n* * * * * * * * * * * * * * * * *   \n");
    printf("* Client %d deconnecte *",pid_client );
    printf("\n* * * * * * * * * * * * * * * * *  \n");
	}
  return 0;
}


/* **************************************** */
/*Fonction handler 1
Le signal SIGURS1 est redirigé sur cette fonction,
Cette fonction change le numéro de la voie à lire à 0 */
/* **************************************** */
void my_handler(int n)
{
  
  num_voie=0;
 /* printf("\nExecution de my_handler par le processus , num_voie = %d\n",num_voie);*/
}

/* **************************************** */
/* Fonction handler 2
Le signal SIGURS2 est redirigé sur cette fonction,
Cette fonction change le numéro de la voie à lire à 1 */
/* **************************************** */
void my_handler2(int n)
{
  num_voie=1;	
 /* printf("\nExecution de my_handler par le processus , num_voie = %d\n",num_voie);*/
}


/* **************************************** */
/***Lecteurs
 * Cette fonction prend en entrée les numéro de sémaphore (pour les opérations P et V)
 * Elle prend également le numéro de voie à lire et le pipe avec le rédacteur
 * Cette fonction récupère l'heure. Elle lit en continue les données du serveur et les envoie directement dans le pipe avec le rédacteur. 
 * **/
/* **************************************** */
void Lecteur(int Sem_lect, int num_voie,int *pfd,int Sem_Serv){
  /*printf("fonction  lecteur  fils %d \n",num_voie);*/
   time_t current_time;
    struct tm * time_info;
    char time_string[9];
    char donnee[L_MSG];
    while(1){
      /*Récupération de l'heure */
      time(&current_time);
      time_info = localtime(&current_time);
      strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);

    /*Fermeture de la lecture du pipe*/
      close(pfd[0]);

    /*demande ressources lecteur et serveur*/
      P(Sem_lect,num_voie);
      P(Sem_Serv,num_voie);

    /*Formatage de la donnée */
      sprintf(donnee,"Data from reader in voie %d is %d  at %s \n",num_voie,(PtrMem+num_voie)->tampon[(PtrMem+num_voie)->n],time_string);
      V(Sem_Serv,num_voie);

    /*Ecriture sur le pipe de la donnée formatée*/
      write(pfd[1],donnee,L_MSG*sizeof(char));
  }
  
}


/* **************************************** */
/** memoire partagee 
 * Cette fonction prend en arguement la taille du buffer à attacher à la mémoire ainsi que la clé d'accès
 * 
 * **/
/* **************************************** */
void  AttacheSegment (int size, char *name)
{

  int shmid ;  /* ID memoire partagee  */
  key_t cle_mem ;  /* clef segment memoire */

  /* On creer une cle identifiant le segement donné*/
  if((cle_mem = ftok(name,C_Shm)) < 0){
    printf("Erreur de creation de la cle memoire !\n");
    exit(1); 
  }

  shmid = shmget(cle_mem,size,0) ; /*Obtention de l'id*/

  if ( shmid== -1 ) 
	{
    		perror("L'obtention de l'ID du segment de memoire partage a echouee") ;
   		 exit(1) ;  /* Exit program */
 	 }

	/*Attachement au segment*/
	PtrMem = (BUF *)shmat(shmid,0,0) ;
 	if (PtrMem ==(BUF*)-1)
  	 {
    		 perror("Attachement memoire partagee impossible") ;
     		exit(1) ;/* Exit program */
     }

  printf("\tTEST:\t ID SEGEMNNT = %d \n",shmid) ;
  printf("\tTEST:\t SEGEMENT ASSOCIE A LA CLE %d \n",cle_mem) ;

}
/* **************************************** */
/* Cette fonction créer un Mutex qui est un ensemble de sémaphore associés à une clé*/
/* **************************************** */
int CreationMutex()
{
  key_t key;
  SEMAPHORE  semid;
  if (( key = ftok(CleServeur,'S')) < 0 )
    return CLEerr;
  semid = semget(key, NVOIES, 0666|IPC_CREAT);
  return semid;
}

/*********************	DESTRUCTION DU MUTEX
 *  ENTREE: semid = identificateur de la famille de semaphores
 *  SORTIE: neant
 *  RETOUR: code erreur -1  ou 0
 */
int DestructionMutex(int semid)
{
  return (semctl(semid, 0, IPC_RMID, 0));
}


/*********************	Initialisation du MUTEX
 *  ENTREE: semid = identificateur de la famille de semaphores
 *  SORTIE: neant
 *  RETOUR: 0 ou SEMerr
 */
int Init_Mutex(int semid, int nb)
{
  struct sembuf semoper;
  int i;
  for(i = 0; i<NVOIES; i++)
    {
      semoper.sem_num = i;
      semoper.sem_op = nb;
      semoper.sem_flg = 0;
      
      if (semop(semid, &semoper, 1) < 0)
	{
	  printf("Erreur Initialisation du Mutex\n");
	  return SEMerr;
	}
    }
  return 0;
}

/*********************	Création du sémaphore
 *  ENTREE: semid = identificateur de la famille de semaphores
 *  SORTIE: neant
 *  RETOUR: 0 ou SEMerr
 */
 SEMAPHORE Creer_sem(key_t cle, unsigned short *val_init)
{
	SEMAPHORE sem;
	int r;
	int nombre_de_sem=2;
	sem = semget(cle, nombre_de_sem,IPC_CREAT|IPC_EXCL|0666);
	if (sem < 0)
	{
		perror("Creer_sem : semget");
		exit(EXIT_FAILURE);
	}
	r = semctl(sem,0,SETALL,val_init);
	if (r <0)
	{
		perror("Creer_sem : semctl");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

/* **************************************** */
/* Destruction d'un ensemble de semaphore   */
/*                                          */
/* On utilise donc semctl avec IPC_RMID     */
/* **************************************** */
void Detruire_sem(SEMAPHORE sem)
{
	/*à la place de nb_sem c'est peut etre 0*/
	int nb_sem = 2;
	if (semctl(sem,nb_sem-1,IPC_RMID,0) != 0)
	{
		perror("Detruire_sem");
		exit(EXIT_FAILURE);
	}	
}

/* **************************************** */
/* Modification de la valeur des semaphores */
/*                                          */
/* appartenant a un ensemble de semaphores. */
/* On utilise donc semop                    */
/* **************************************** */
void Changer_sem(SEMAPHORE sem, int val, int NumSemaphore)
{
	struct sembuf sb[1];
	sb[0].sem_num = NumSemaphore;
	sb[0].sem_op = val;
	sb[0].sem_flg=0;

	if (semop(sem,sb,1) != 0)
	{
		perror("Changer_sem");
		exit(EXIT_FAILURE);
	}  
}

/* **************************************** */
/*Fonction P sémaphore, prend l'ensembnle de sémaphore en entrée et le numéro */
/* **************************************** */
void P(SEMAPHORE sem, int NumSemaphore)
{
	Changer_sem(sem,-1, NumSemaphore);
}

/* **************************************** */
/*Fonction V sémaphore, prend l'ensembnle de sémaphore en entrée et le numéro */
/* **************************************** */
void V(SEMAPHORE sem, int NumSemaphore)
{
	Changer_sem(sem,1, NumSemaphore);
}

/* **************************************** */
/*Fonction Rédacteur 
Cette fonction lit 5 données dans le pipe_lecteur, 
Il concatène les données dans un tampon puis les envoie dans le pipe du driver. 
Il remet le tampon à 0 et recommence la lecture 
 */
/* **************************************** */
void Redacteur (int numlect,int *pfd) 
{ 
	char donnee[L_MSG];
  char Tampon[BUF_SZ];
  Tampon[0] = '\0';
  int i=0;
  /*Fermeture du pipe du lecteur en écriture*/
	close(pfd[1]);
	while (1)
	{			
    if(i==5)
		{
			i=0;
      /*printf("redacteur\n");*/
      strcat(Tampon,"\n");
      close(pfd_driver[0]);
      FILE *pipe_out = fdopen(pfd_driver[1], "w");
            fprintf(pipe_out, "%s", Tampon);
            fflush(pipe_out);
            fclose(pipe_out);
			Tampon[0] = '\0';
		}
    /*Lecture d'une donnée sur le pipe du lecteur*/
		read(pfd[0],&donnee, sizeof(char)*L_MSG);
    strcat(Tampon,donnee);
		fflush(stdout);
    i++;
	}
	
		
}
