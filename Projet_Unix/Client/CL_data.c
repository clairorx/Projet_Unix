/**********************************************************
*						  	  *
*		       Fichier CL_data.c                   *
*							  *
**********************************************************/
#include "CL_include"

/* */
void read_data(int shmid, BUF **MemBuf){
    printf("data in MemBuf->tampon[%d] is %d", (*MemBuf)->n, (*MemBuf)->tampon[(*MemBuf)->n]);
    
}