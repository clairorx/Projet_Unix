/**********************************************************
*						  	  *
*		     Fichier CL_redacteur.c  			               *
*							  *
**********************************************************/

#include "CL_include"

/**/
void main_redacteur(int voie, int sem_redact, int* pfd){
    char data[5][100];
    close(pfd[1]);
    int i=0;
    int j = 0;
    int k = 0;
    while(1){
        for(j=0; j<5; j++){
            /* le redacteur attend la lecture de donnee */
            read(pfd[0], data[j], sizeof(data[j]));
            i++;
        }
        for(k=0; k<j; k++){
            printf(" Donnee no %d de la voie %d : %s\n",k+i-5,voie,data[k]);
        } 
        printf("\n");
    }
}