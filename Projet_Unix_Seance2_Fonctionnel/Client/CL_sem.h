/**********************************************************
*						  	  *
*		                Fichier CL_sem.h                  *
*							  *
**********************************************************/


typedef int SEMAPHORE;

SEMAPHORE Sem_create();
void Sem_destroy(SEMAPHORE);


int P(SEMAPHORE sem, int voie);
int V(SEMAPHORE sem, int voie);

