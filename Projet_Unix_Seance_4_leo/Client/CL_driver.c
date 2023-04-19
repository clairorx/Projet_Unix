/********************************************************
*	Fichier CL_driver.c				*
*-----------------------------------------------------------------------*
Chaumette/Festoc/Pieau
14/04/2023
************************************************************************/
/* fichier include */
#include "CL_include"

int main(void) /*Ce fichier lis simplement l'entrée standard qui a été remplacée par un tube dans Cl.c*/
{
   
		char DataMessage;
        printf("Bienvenu dans le driver\n");
        while(1)
        { 
            scanf("%c",&DataMessage);
            printf("%c",DataMessage);
            /*DataMessage[0]='\0';*/
		
            
        }
		return 0;
}

/*
gcc -c CL_driver.c 
gcc  CL_Driver.o -o DRIVER.EXE
*/

