/**********************************************************
*						  	  *
*		     Fichier CL_sem.c                     *
*							  *
**********************************************************/
#include "CL_include"
#include "CL_sem.h"

/* Creation de semaphore */
 SEMAPHORE Creer_sem()
{
	SEMAPHORE sem;
	int r;
	int nombre_de_sem=2;
	unsigned short val_init[2]={0, 0};
	sem = semget(IPC_PRIVATE, nombre_de_sem,IPC_CREAT|IPC_EXCL|0666);
	if (sem < 0)
	{
		perror("Creer_sem : semget");
		exit(EXIT_FAILURE);
	}
	r = semctl(sem,0,SETALL,val_init);
	if (r <0)
	{
		perror("Creer_sem : semctl");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

/* Destruction des semaphores */
void Detruire_sem(SEMAPHORE sem)
{
	/*à la place de nb_sem c'est peut etre 0*/
	int nb_sem = 2;
	if (semctl(sem,nb_sem-1,IPC_RMID,0) != 0)
	{
		perror("Detruire_sem");
		exit(EXIT_FAILURE);
	}	
}

/* Modification de la valeur des semaphores*/
void Changer_sem(SEMAPHORE sem, int val, int NumSemaphore)
{
	struct sembuf sb[1];
	sb[0].sem_num = NumSemaphore;
	sb[0].sem_op = val;
	sb[0].sem_flg=0;

	if (semop(sem,sb,1) != 0)
	{
		perror("Changer_sem");
		exit(EXIT_FAILURE);
	}  
}


void P(SEMAPHORE sem, int NumSemaphore)
{
	Changer_sem(sem,-1, NumSemaphore);
}

void V(SEMAPHORE sem, int NumSemaphore)
{
	Changer_sem(sem,1, NumSemaphore);
}


/* Creation de cle avec ftok */
key_t Creer_cle(char *nom_fichier)
{
	key_t cle;
	if ( (cle = ftok(nom_fichier,'0')) == -1)
	{
		perror("Creer_cle");
		exit(EXIT_FAILURE);
	}
	return (cle);
}
