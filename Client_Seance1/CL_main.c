/**********************************************************
*						  	  *
*		     Fichier CL_main.c                    *
*							  *
**********************************************************/

#include "CL_include"
#include "CL_msg.h"
#include "CL_mem.h"
#include "CL_connect.h"

/* Definition de fonction */
void my_handler(int);

/* Definition d'une variable globale */
int voie = 0;



int main(int argc, char *argv[]) {

	/* IDENTIFICATION DE LA MESSAGERIE PAR LE CLIENT */
	printf("IDENTIFICATION MESSAGERIE\n");
	key_t cleS = cle_serveur(CleServeur, C_Msg); /* Création de la clé serveur */
	int idMes = id_messagerie(cleS); /* Obtention de l'id de la messagerie à partir de la clé CleServeur */
	printf("IDENTIFICATION TERMINEE\n");

	

	/* CONNEXION */
	printf("\nDEMANDE DE CONNEXION AU SERVEUR\n");
	envoi_connect(idMes, L_MSG); /* Envoi du message de type CONNECT au seveur */
	dmsgbuf messageClient = reception_client(idMes, L_MSG); /* Client reçoit de la part du serveur le message avec la cle client */
	key_t cleC = cle_client(messageClient.txt, C_Shm); /* Obtention  la clé client avec ftok à partir du message */
	envoi_ack(idMes, L_MSG); /* Envoi de l'acquittement */
	printf("CONNECTE AU SERVEUR\n");


	/* OBTENTION DE L'ID DE MEMOIRE PARTAGEE*/
	printf("\nOBTENTION DE L'ID DE MEMOIRE PARTAGEE\n");
	int shmid = id_mem(cleC, BUF_SZ); 
	BUF* buffer = NULL; 
	buffer = adr_mem(shmid); /* Obtention de l'adresse de la memoire partagee */


 	/* CREATION DU SEGMENT DE MEMOIRE PARTAGEE */
	printf("\nCREATION DU SEGMENT DE MEMOIRE PARTAGEE\n");
	int memid;
	key_t cle2 = 1001;
	if ((memid = shmget(cle2, sizeof(int), IPC_CREAT | 0600)) == -1) {
		printf("Erreur lors de la creation de l'id de la memoire partagee ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* ATTACHEMENT ET INITIALISATION DE LA MEMOIRE PARTAGEE */
	printf("\n ATTACHEMENT ET INITIALISATION DE LA MEMOIRE PARTAGEE\n");
	BUF* ptr;
	ptr = (BUF *) shmat(memid,0,0);
	printf("SEGMENT ATTACHE A LA MEMOIRE PARTAGEE\n");

	
	/* RECEPTION DES SIGNAUX */
	printf("ATTENTE DE RECEPTION DES SIGNAUX\n");
	signal(SIGUSR1, my_handler);
	signal(SIGUSR2, my_handler);

	/* LECTURE DES VOIES ET AFFICHAGE DES DONNEES RECUES */
	printf("AFFICHAGE DES DONNEES RECUES : \n");

	/* Je n'arrive pas à trouver la condition pour que ma boucle d'affichage s'arrête */
	/* J'ai essayé de récupérer le temps de marche du client pour faire comme un compteur mais ça ne doit surement pas marcher comme ça */
	/*int nbdata,compteur;
	nbdata=atoi(argv[1]);
	sprintf(argv[1],"%d",abs(nbdata));
	compteur= argv[1];
	while(compteur!=0){*/

	while(1){
	  pause(); /* Attente de l'arrivée du signal */
	  if(voie==0){
	    printf("%d\n", ptr->tampon[ptr->n]);}
	  if(voie==1){
	    printf("%d\n",(ptr+1)->tampon[(ptr+1)->n]);
	  }
	  /* compteur--; /* Decrementation du compteur */
	}


  	/* Détachement et destruction du segment de mémoire partagée */
  	shmdt(ptr);
	shmctl(memid, IPC_RMID, NULL);
	printf("\nDESTRUCTION MEMOIRE PARTAGEE\n");


	/* FIN */
	printf("\n\nFin du client\n");

	return EXIT_SUCCESS;
}


void my_handler(int a){
  if(a==10) voie = 0;
  if(a==12) voie = 1;
  printf("Signal sur voie %d reçu : ",voie+1);
  printf("\n");
}
