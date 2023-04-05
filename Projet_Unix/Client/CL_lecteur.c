/**********************************************************
*						  	  *
*		     Fichier CL_lecteur.c  			               *
*							  *
**********************************************************/

#include "CL_include"

/**
 * @brief Fonction qui permet de lire les données dans la mémoire partagée
 * 
 * @param voie 
 * @param sem 
 * @param MemBuf 
 * @param limiteN 
 */
void main_lecteur(int voie,int sem_redact, int sem_lect, BUF **MemBuf, int limiteN, int* pfd){
	while(((*(MemBuf)+0)->n + (*(MemBuf)+1)->n)<limiteN){
		P(sem_lect,voie);
		P(sem_redact,ECRITURE);
		read_data(voie, MemBuf, pfd);
		V(sem_redact,LECTURE);
	}
}
