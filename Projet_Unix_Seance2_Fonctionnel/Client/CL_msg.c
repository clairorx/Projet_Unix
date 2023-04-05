/**********************************************************
*						  	  *
*		            Fichier CL_msg.c                         *
*							  *
**********************************************************/

#include "CL_include"

/****************	CREATION DE LA MESSAGERIE
*  ENTREE: Neant
*  SORTIE: la messagerie est cree
*  RETOUR: code erreur <0 ou identifcateur de la messagerie
*/
int CreationMessagerie(){
   key_t key;
   int  msqid; /* identificateur de la messagerie */
   if (( key = ftok(CleServeur,C_Msg)) < 0 )
      return CLEerr; 
   msqid = msgget(key,0666|IPC_CREAT);
   printf("On est dans la création messagerie");
   return msqid;
}


/*********************	RELACHE LA MESSAGERIE
*  ENTREE: msqid = identificateur de la messagerie
*  SORTIE: neant
*  RETOUR: code erreur -1  ou 0
*/
int RelacheMessagerie(int msqid){
   return (msgctl(msqid,IPC_RMID,NULL));
}
