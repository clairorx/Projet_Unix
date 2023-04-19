/**********************************************************
*						  	  *
*		     Fichier CL_mem.c                     *
*							  *
**********************************************************/


#include "CL_include"

/**
 * @brief Fonction qui permet de créer la mémoire partagée
 * 
 * @param Ptr 
 * @param CleClient 
 * @return int 
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

/**
 * @brief Fonction qui permet de relacher la mémoire partagée
 * 
 * @param Tshmid 
 * @param Cshmid 
 * @return int 
 */
int RelacheMemoires(int Tshmid, int Cshmid){
    int ret = 0;

    if (Tshmid)
        ret = shmctl(Tshmid,IPC_RMID,NULL);
    if (Cshmid)
        ret += shmctl(Cshmid,IPC_RMID,NULL);
    return ret;
}

