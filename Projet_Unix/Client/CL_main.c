/**********************************************
 * Projet Unix - Client
 * 	
 * Taches 
*/
#include "CL_include"

static void end(); 
static int Msqid;

int main(){
	printf("Test Client\n");
	Msqid = CreationMessagerie();
	printf("msqid = %d\n", Msqid);
	return 0;
}

static void end() { 
  printf("\nSrv:FIN Mort du fils receptionniste \n");
  printf("Srv:FIN Mort du fils informateur \n");
  printf("\nSrv:FIN RelachMsg %d\n", RelacheMessagerie(Msqid));
  kill(0,SIGKILL); /* on tue tout le monde */
}