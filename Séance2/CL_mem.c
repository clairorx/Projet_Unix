/**********************************************************
*						  	  *
*		     Fichier CL_mem.c                     *
*							  *
**********************************************************/

/*OBTENTION DE L'ID DE LA MEMOIRE PARTAGEE */

#include "CL_include"
#include "CL_mem.h"

/*Obtention de l'id de la memoire partagee */
int id_mem(key_t CleC, int BUF_S) {

	int shmid;

	if ((shmid = shmget(CleC, BUF_S, 0600)) == -1) {
		printf("Erreur lors de l'obtention de l'id du tampon: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else 
		printf("Clt: ID tampon = %d\n", shmid);

	return shmid;
}

/*Obtention de l'adresse de la memoire partagee*/
BUF* adr_mem(int shmid) {

	BUF* buffer;

	if ((buffer = (BUF*) shmat(shmid, NULL, 0)) == -1) {
		printf("Erreur lors de l'obtention de l'adresse de la memoire partagee: ");
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	else 
		printf("Clt: ADRESSE tampon = 0x%x\n", buffer);

	return buffer;
}
