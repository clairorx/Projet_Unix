/**********************************************************
*						  	  *
*		                Fichier CL_sem.c                  *
*							  *
**********************************************************/

#include "CL_include"

/**
 * @brief Création de deux sémaphores
 * 
 * @return SEMAPHORE 
 */
SEMAPHORE Sem_create(){

    int array[2] = {0,0};
    SEMAPHORE sem; 
    int nombre_sem = 2; /* Pour libérer la voie 1 ( donc 0 ) ou la voie 2 ( donc 1 )*/
    sem = semget(IPC_PRIVATE, nombre_sem, 0666 | IPC_CREAT);
    if (sem == -1){
        perror("Erreur lors de la creation du semaphore");
        exit(1);
    }  
    semctl(sem, 0, SETALL, array);
    return (sem);
}

/**
 * @brief Destruction des semaphores
 * 
 */
void Sem_destroy(SEMAPHORE sem){
    
    int nombre_sem = 2; 
    if(semctl(sem,nombre_sem-1,IPC_RMID, 0) != 0){
        perror("Erreur lors de la destruction du semaphore");
        exit(1);
    }
}
/**
 * @brief Initialisation des semaphores
 * 
 * @param sem 
 * @param val 
 * @param NUMSemaphore 
 * @return int 
 */
int P(SEMAPHORE sem, int voie)
{
    struct sembuf semoper;
    semoper.sem_num = voie;
    semoper.sem_op = -1;
    semoper.sem_flg = 0;
    
    if (semop(sem, &semoper, 1)!= 0)
        {
        perror("Erreur P sur le Semaphore");
        return SEMerr;
        }
    
    return 0;
}

/**
 * @brief 
 * 
 * @param semid 
 * @param voie 
 * @return int 
 */
int V(SEMAPHORE sem, int voie){

    struct sembuf semoper;
    semoper.sem_num = voie;
    semoper.sem_op = 1;
    semoper.sem_flg = 0;
  
    if (semop(sem, &semoper, 1) < 0)
    {
        perror("Erreur V sur le Semaphore");
        return SEMerr;
    }
  
    return 0;
}



