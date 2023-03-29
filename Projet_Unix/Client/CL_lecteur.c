/**********************************************************
*						  	  *
*		     Fichier CL_lecteur.c                 *
*							  *
**********************************************************/

#include "CL_include"

void main_lecteur(int voie, int sem, BUF **MemBuf){
	printf("Dans le lecteur de la voie %d\n",voie);
	while(1){
		printf("lecteur voie %d demande ressource\n",voie);
		P(sem,voie);
		printf("lecteur voie %d ressource obtenue\n",voie);
		read_data(voie, MemBuf);
	}
	
}
