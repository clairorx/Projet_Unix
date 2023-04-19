/**********************************************************
*						  	  *
*		     Fichier CL_redacteur.c  			               *
*							  *
**********************************************************/

#include "CL_include"

/**
 * @brief Fonction Redacteur
 * 
 * @return int 
 */
void main_redacteur(int voie, int sem_driver, int* pfd, int pfd_driver[2]){

    char data[5][100];
    char data_driver[100];
    close(pfd[1]);
    close(pfd_driver[0]);

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
            sprintf(data_driver," Donnee no %d de la voie %d : %s\n",k+i-5,voie,data[k]);
            P(sem_driver,0);
            write(pfd_driver[1], data_driver, sizeof(char)*100);
            V(sem_driver,0);
        } 
        sprintf(data_driver,"\n");
        P(sem_driver,0);
        write(pfd_driver[1], data_driver, sizeof(char)*100);
        V(sem_driver,0);
    }
}