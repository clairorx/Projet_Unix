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
void main_lecteur(int voie, int sem, BUF **MemBuf, int limiteN){
	while(((*(MemBuf)+0)->n + (*(MemBuf)+1)->n)<limiteN){
		P(sem,voie);
		read_data(voie, MemBuf);
	}
}
