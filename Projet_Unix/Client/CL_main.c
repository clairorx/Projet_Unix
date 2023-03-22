/**********************************************
 * Projet Unix - Client
 * 	
 * Taches 
*/
#include "CL_include"

static void end(); 
static int Msqid;
static int CleClient;
int main(){
	printf("Test Client\n");
	Msqid = CreationMessagerie();
	printf("msqid = %d\n", Msqid);

	ConnectServeur(Msqid, &CleClient);
	printf("Cle client = %d\n", CleClient);
	return 0;
}

static void end() { 
  printf("\nSrv:FIN Mort du fils receptionniste \n");
  DeconnectServeur(Msqid);

  printf("\nSrv:FIN RelachMsg %d\n", RelacheMessagerie(Msqid));
  kill(0,SIGKILL); /* on tue tout le monde */
}
