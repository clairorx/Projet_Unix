/**********************************************************
*						  	  *
*		     Fichier CL_driver.c                 *
*							  *
**********************************************************/

#include "CL_include"

/**
 * @brief Fonction qui lit l'entrée standard et l'affiche
 * 
 * @return int 
 */
int main_driver(int pfd_driver[2]) 
{   
    close(pfd_driver[1]);
    char DataMessage[100];
    printf("Bienvenu dans le driver\n");
    while(1)
    { 
        read(pfd_driver[0], &DataMessage, sizeof(char)*100);
        printf("%s", DataMessage);
    }
}

