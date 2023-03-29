/**********************************************************
*						  	  *
*		       Fichier CL_msg.c                   *
*							  *
**********************************************************/

/*IDENTIFICATION DE LA MESSAGERIE PAR LE CLIENT*/

#include "CL_include"
#include "CL_msg.h"


/* Création de la clé serveur*/
key_t cle_serveur(char* CleServ, int Msg) {

	key_t CleS;

	if ((CleS = ftok(CleServ, Msg)) == -1) {
		printf("Erreur lors de la creation de la cle serveur: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
	
		printf("Clt: IPC cle serveur = %d\n", CleS);

	return CleS;
}
	
	
/* Obtention de l'id de la messagerie avec la commande msgget à partir de la clé CleServeur */
int id_messagerie (key_t CleS) {

	int id_mes;
		
	if ((id_mes = msgget(CleS, IPC_CREAT)) == -1) {
		printf("Erreur lors de l'obtention de l'id de la messagerie: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: ID messagerie = %d\n", id_mes);
	
	return id_mes;
}
