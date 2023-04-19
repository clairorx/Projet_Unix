/********************************************************
*	Module CL.c				*
*-----------------------------------------------------------------------*
					*
************************************************************************/
#include "CL_include"

int main(int argc,char *argv[])
{
  int  nbdata,t_reste;
  
  
  if (argc < 2)
    {
      printf("\n!!!! Usage : CL  <+/-nombre de donnees>\n");
      exit(0);
   }
  nbdata=atoi(argv[1]);
  if (nbdata==0)
    {
      printf("\n!!!! nombre de donnees DIFFERENT de 0\n");
      exit(0);
    }
  sprintf(argv[1],"%d",abs(nbdata));
  
  /*  Lancement du client  */
  printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * \n");
  printf(" Projet CLIENT - SERVEUR Unix IESE4 2022-2023\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * \n");
  printf("\nLancement du client pendant %s s\n",argv[1]);
 
  if (execlp("./cl_zz","./cl_zz",argv[1],(char *)00) == -1)
    {
      printf("Erreur de execlp\n");
    }
  
  return 0;
}

