/**********************************************************
*						  	  *
*		     Fichier CL_mem.c                     *
*							  *
**********************************************************/


#include "CL_include"
#include "CL_mem.h"

/*************   ALLOCATION D'UN TAMPON DE DONNEES
*  ENTREE: Ptr = pointeur du pointeur du tampon
*  SORTIE: le pointeur est renseigne
*  RETOUR: code erreur <0 ou identificateur de la memoire
*/
int CreationSharedMemory(BUF **Ptr, key_t CleClient){
    BUF *MemTamponPtr;
    int CLTshmid;
    if ((CLTshmid = shmget(CleClient,2*sizeof(BUF),0666|IPC_CREAT)) <0){
        return SHMerr;
    }
    if ((MemTamponPtr = (BUF *)shmat(CLTshmid,NULL,0)) == 0 ){
        return SHMerr;
    }
    *Ptr = MemTamponPtr; 
    return CLTshmid;
}

/*********************	DESALLOCATION DES TAMPONS
*  ENTREE: Tshmid,Cshmid = ID des memoires partagee
*  SORTIE: neant
*  RETOUR: code erreur <0 ou  0 ;
*/
int RelacheMemoires(int Tshmid, int Cshmid){
    int ret = 0;

    if (Tshmid)
        ret = shmctl(Tshmid,IPC_RMID,NULL);
    if (Cshmid)
        ret += shmctl(Cshmid,IPC_RMID,NULL);
    return ret;
}

