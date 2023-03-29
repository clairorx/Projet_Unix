/**********************************************************
*						  	  *
*		        Fichier CL.c                      *
*							  *
**********************************************************/
#include "CL_include"

int main(int argc,char *argv[])
{
  int  nbdata;
  
  
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
  
  /*  LANCE LE CLIENT  */
  printf("Projet CLIENT - IESE 4 - 2020\n\n");

  printf("\n******************************************\n");
  printf("Lancement du client (pendant %s s)\n",argv[1]);
  printf("******************************************\n\n");
 

  if (execlp("./cl_zz","./cl_zz",argv[1],(char *)00) == -1)
    {
      printf("Erreur de execlp\n");
    }
  
  return 0;
}

