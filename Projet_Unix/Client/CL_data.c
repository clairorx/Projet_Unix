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
void read_data(int voie, BUF **MemBuf, int* pfd){
    char str[100];
    close(pfd[0]);
    sprintf(str, "%d", ((*(MemBuf)+voie)->tampon[(*(MemBuf)+voie)->n]));
    printf("Dans read data, data = %s\n", str);
    write(pfd[1], str, sizeof(str));
}