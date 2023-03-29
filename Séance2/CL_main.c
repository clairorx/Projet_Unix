/**********************************************************
*						  	  *
*		     Fichier CL_main.c                    *
*							  *
**********************************************************/

#include "CL_include"
#include "CL_msg.h"
#include "CL_mem.h"
#include "CL_sem.h"


/* Prototype de fonction */
void my_handler(int);

/* Definition d'une variable globale */
int voie = 0;

/* FONCTION MAIN */
int main(int argc, char *argv[]){

  /* DECLARATION DES VARIABLES */
  int tps;               /* temps d'execution */
  int idMes;                   /* ID de la messagerie */
  key_t cleC;                  /* clé client */
  dmsgbuf messageClient;       /* message reçu par le serveur contenant la cle de connexion */
  int shmid;                   /* ID de la memoire partagee */
  BUF *buffer = NULL;          /* Adresse de la memoire partagee */
  BUF *ptr;
  /* long int c_pid = getpid();   /* pid du client/pere */          
  long int pidf1, pidf2;       /* pid des fils/lecteurs */
  SEMAPHORE sem = Creer_sem(); /* Creation des semaphores */
  int i;

  /* VALIDATION DU NOMBRE D ARGUMENTS RECUS */
  if(argc < 2){
    printf("Erreur : un argument est obligatoire ! Ex. ./CL <time>\n");
    exit(1); /* en cas d'erreur on arrête l execution */
  }
  
  /* AFFICHAGE DU TEMPS D EXECUTION DU CLIENT */
  tps=atoi(argv[1]);
  sprintf(argv[1],"%d",abs(tps));

  printf("Projet CLIENT - IESE 4 - 2020\n\n");
  printf("\n******************************************\n");
  printf("Lancement du client (pendant %d s)\n",tps);
  printf("******************************************\n\n");
  if (execlp("./cl_zz","./cl_zz",argv[1],(char *)00) == -1)
    {
      printf("Erreur de execlp\n");
    }


  /* IDENTIFICATION DE LA MESSAGERIE PAR LE CLIENT ET CONNEXION */
  printf("IDENTIFICATION MESSAGERIE\n");
  idMes = connect_messagerie(CleServeur, C_Msg); /* Creation de la cle et obtention de l'id de la messagerie a partir de la cle serveur */
  printf("\nDEMANDE DE CONNEXION AU SERVEUR\n");
  envoi_connect(idMes, L_MSG); /* Envoi du message de type CONNECT au serveur */
  messageClient = reception_client(idMes, L_MSG); /* CLient recoit de la part du serveur le message avec la cle client */
  cleC = cle_client(messageClient.txt, C_Shm); /* OBtention de la cle client avec ftok a partir du message */
  envoi_ack(idMes, L_MSG);
  printf("CONNECTE AU SERVEUR\n");


  /* OBTENTION DE L'ID DE LA MEMOIRE PARTAGEE */
  printf("\nOBTENTION DE L'ID DE MEMOIRE PARTAGEE\n");
  shmid = id_mem(cleC, BUF_SZ); 
  buffer = adr_mem(shmid); /* Obtention de l'adresse de la memoire partagee */

  
  /* ATTACHEMENT A LA MEMOIRE PARTAGEE */
  printf("\nATTACHEMENT DE LA MEMOIRE PARTAGEE\n");
  ptr = (BUF *) shmat(shmid,0,0);
  printf("ATTACHE A LA MEMOIRE PARTAGEE\n");

  /* RECEPTION DES SIGNAUX ET LECTURE */
  if((pidf1=fork()) == -1) {
    perror("ERREUR : Création du fils 1\n");
    exit(EXIT_FAILURE);
  }

  /* Creation des fils lecteurs  et lecture des donnees */
  printf("AFFICHAGE DES DONNEES RECUES : \n");

  if(pidf1){ /* Code du père */
    if(pidf2 = fork()){ /* Code du père */
        signal(SIGUSR1, my_handler);
	signal(SIGUSR2, my_handler);
	for(i=0;i<10;i++){
	  pause();
	  if(voie==0){
	    V(sem,0);
	  }
	  else{
	    V(sem,1);
	  }
	}
    }
    else{ /* Code du fils lecteur 1 */
      printf("Signal recu sur voie 1 : ");
      P(sem,0);
      printf("%d\n", ptr->tampon[ptr->n]);
      exit(0);
    }
  }
  else{ /* Code du fils lecteur 2 */
      printf("Signal recu sur voie 2 : ");
      P(sem,1);
      printf("%d\n",(ptr+1)->tampon[(ptr+1)->n]);
      exit(0);
  }
  wait(pidf1);
  wait(pidf2);
  Detruire_sem(sem); 

  
  /* DETACHEMENT DE LA MEMOIRE PARTAGEEE */
  shmdt(ptr);

  /* DECONNEXION DE LA MESSAGERIE */
  envoi_deconnect(idMes, L_MSG);
  

  /* FIN */
  printf("FIN DU CLIENT\n");
  
  return EXIT_SUCCESS;
}



void my_handler(int a){
  if(a==10) voie = 0;
  if(a==12) voie = 1;
  printf("Signal sur voie %d reçu : ",voie+1);
  printf("\n");
}
