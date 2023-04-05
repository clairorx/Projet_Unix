/**********************************************************
*						  	  *
*		     Fichier CL_redacteur.c  			               *
*							  *
**********************************************************/

#include "CL_include"

/**/
void main_redacteur(int voie, int sem_redact, int* pfd, int limiteN){
    char data[5][100];
    close(pfd[1]);
    int i=0;
    int j = 0;
    int k = 0;
    V(sem_redact, ECRITURE);
    while(i< limiteN){
        for(j=0; j<5; j++){
            /* le redacteur attend la lecture de donnee */
            P(sem_redact, LECTURE);
            read(pfd[0], data[j], sizeof(data[j]));
            printf("%s\n", data[j]);
            V(sem_redact, ECRITURE);
            i++;
            if(i>=limiteN) break;
        }
        for(k=0; k<j; k++){
            printf(" Voie n° %d : data n° %d = %s\n",voie, k+i-5, data[k]);
        }
    
   

    }
}