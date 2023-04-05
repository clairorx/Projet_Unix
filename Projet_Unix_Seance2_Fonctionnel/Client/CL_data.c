/**********************************************************
*						  	  *
*		       Fichier CL_data.c                   *
*							  *
**********************************************************/
#include "CL_include"

/* */
void read_data(int voie, BUF **MemBuf){
    printf("data in MemBuf->tampon[%d] is %d\n", (*(MemBuf)+voie)->n, (*(MemBuf)+voie)->tampon[(*(MemBuf)+voie)->n]);

}