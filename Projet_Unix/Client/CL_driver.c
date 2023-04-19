/**********************************************************
*						  	  *
*		     Fichier CL_driver.c                 *
*							  *
**********************************************************/

#include "CL_include"

/**
 * @brief Programme qui lit l'entrée standard et l'affiche
 * 
 * @return int 
 */
int main(){   
    char DataMessage;
    printf("Bienvenu dans le driver\n");
    while(1){ 
        scanf("%c",&DataMessage);
        printf("%c", DataMessage);
    }
    return 0;
}

