/**********************************************************
*						  	  *
*		            Fichier CL_msg.c                         *
*							  *
**********************************************************/

#include "CL_include"

/**
 * @brief Crée la messagerie
 * 
 * @return int 
 */
int CreationMessagerie(){
   key_t key;
   int  msqid; /* identificateur de la messagerie */
   if (( key = ftok(CleServeur,C_Msg)) < 0 )
      return CLEerr; 
   msqid = msgget(key,0666|IPC_CREAT);
   /*printf("On est dans la création messagerie");*/
   return msqid;
}


/**
 * @brief Envoie un message
 * 
 * @param msqid 
 * @param message 
 * @param type 
 * @return int 
 */
int RelacheMessagerie(int msqid){
   return (msgctl(msqid,IPC_RMID,NULL));
}
