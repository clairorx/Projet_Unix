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
int driver(int pfd_driver[2]) 
{   
    close(pfd_driver[1]);
    char DataMessage;
    printf("Bienvenu dans le driver\n");
    while(1)
    { 
        read(pfd_driver[0], &DataMessage, sizeof(DataMessage));
        printf("%c", DataMessage);
    }
}

