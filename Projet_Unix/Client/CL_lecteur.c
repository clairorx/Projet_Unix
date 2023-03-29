/**********************************************************
*						  	  *
*		     Fichier CL_lecteur.c                 *
*							  *
**********************************************************/

#include "CL_include"

void main_lecteur(int voie, int sem, BUF **MemBuf, int limiteN){
	while(((*(MemBuf)+0)->n + (*(MemBuf)+1)->n)<limiteN){
		P(sem,voie);
		read_data(voie, MemBuf);
	}
}
