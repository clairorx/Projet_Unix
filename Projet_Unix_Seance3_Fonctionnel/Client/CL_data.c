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
    time_t now;
    time(&now);
    char str[100];
    close(pfd[0]);
    sprintf(str, "%d %s", ((*(MemBuf)+voie)->tampon[(*(MemBuf)+voie)->n]),ctime(&now));
    str[strlen(str)-1] = '\0';
    write(pfd[1], str, sizeof(str));
}