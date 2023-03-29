#ifndef CL_SEM
#define CL_SEM

typedef int SEMAPHORE;

SEMAPHORE Creer_sem();
void Detruire_sem(SEMAPHORE sem);
void Changer_sem(SEMAPHORE sem, int val, int NumSemaphore);
void P(SEMAPHORE sem, int NumSemaphore);
void V(SEMAPHORE sem, int NumSemaphore);
key_t Creer_cle(char *nom_fichier);


#endif


