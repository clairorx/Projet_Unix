/**********************************************************
*						  	  *
*		       Fichier CL_data.c                   *
*							  *
**********************************************************/
#include "CL_include"

/**
 * @brief Fonction qui permet de lire les données dans la mémoire partagée
 * 
 * @param voie
 * @param MemBuf 
 */
void read_data(int voie, BUF **MemBuf){
    printf("data in MemBuf->tampon[%d] is %d\n", (*(MemBuf)+voie)->n, (*(MemBuf)+voie)->tampon[(*(MemBuf)+voie)->n]);

}