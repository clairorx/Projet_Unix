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
void main_lecteur(int voie, int sem_lect, BUF **MemBuf, int* pfd){
    close(pfd[0]);
	while(1){
		P(sem_lect,voie);
		read_data(voie, MemBuf, pfd);
	}
}
