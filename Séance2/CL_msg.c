/**********************************************************
*						  	  *
*		       Fichier CL_msg.c                   *
*							  *
**********************************************************/

/*IDENTIFICATION DE LA MESSAGERIE PAR LE CLIENT*/

#include "CL_include"
#include "CL_msg.h"


key_t connect_messagerie(char* CleServ, int Msg) {

  /* Obtention de la cle de messagerie */
	key_t CleMes;

	if ((CleMes = ftok(CleServ, Msg)) == -1) {
		printf("Erreur lors de la creation de la cle serveur: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else {
		printf("Clt: Cle de messagerie = %d\n", CleMes);
	}

	/* Obtention de l'id de la messagerie */

	int id_mes;
		
	if ((id_mes = msgget(CleMes, IPC_CREAT)) == -1) {
		printf("Erreur lors de l'obtention de l'id de la messagerie: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else {
		printf("Clt: ID messagerie = %d\n", id_mes);
	}
	return id_mes;
}


/* CONNEXION A LA MESSAGERIE */


/*Envoi du message de type CONNECT au seveur*/
void envoi_connect(int id_mes, int L) {

	dmsgbuf message_connect;
	message_connect.type = CONNECT;
	sprintf(message_connect.txt, "%d", getpid());
	
	if (msgsnd(id_mes, &message_connect, L, IPC_NOWAIT) == -1) {
		printf("Erreur lors de l'envoi du MESSAGE %s type CONNECT: ", message_connect.txt);
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: Envoi MESSAGE %s type CONNECT\n", message_connect.txt);
}
		
/* Client reçoit de la part du serveur le message avec la cle client*/
dmsgbuf reception_client(int id_mes, int L) {

	dmsgbuf message_client;

	if (msgrcv(id_mes, &message_client, L, getpid(), 0) == -1) {
		printf("Erreur lors de la reception du message en provenance du serveur: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: Recu MESSAGE - Cle client = %s\n", message_client.txt);

	return message_client;
}
	
/*Obtention  la clé client avec ftok à partir du message*/
int cle_client(char* message, int Shm) {
	
	int CleC;

	if ((CleC = ftok(message, Shm)) == -1) {
		printf("Erreur lors de la creation de la cle client: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: IPC cle client = %d\n", CleC);

	return CleC;
}
		
/*Envoi de l'acquittement*/
void envoi_ack(int id_mes, int L) {

	dmsgbuf message_ack;
	message_ack.type = ACK;
	sprintf(message_ack.txt, "%i", getpid());
	
	if (msgsnd(id_mes, &message_ack, L, IPC_NOWAIT) == -1) {
		printf("Erreur lors de l'envoi du message type ACK: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: Envoie MESSAGE type ACK\n");
}


/* Deconnexion du client */
void envoi_deconnect(int id_mes, int L) {

	dmsgbuf message_deco;
	message_deco.type = DECONNECT;
	sprintf(message_deco.txt, "%i", getpid());
	
	if (msgsnd(id_mes, &message_deco, L, IPC_NOWAIT) == -1) {
		printf("Erreur lors de l'envoi du message type DECONNECT: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: Envoie MESSAGE type DECONNECT\n");
}
