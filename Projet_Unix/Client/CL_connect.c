/* Fichier CV_connect.c  */


#include "CL_include"

void AlarmeTimeout(int s){};

void MsgTimout(int n)
{
signal(SIGALRM,AlarmeTimeout);
alarm(n);
}

/**********************************************
*	ENREGISTREMENT DES ARRIVEES ET DEPARTS
*
* ENTREE: msqid = identifiant de la messagerie
*	 : Cptr = pointeur sur la table des PID clients
*  SORTIE: ce processus doit etre detruit par le processus pere
*  RETOUR: -1 Si erreur sur msgrcv
*/


void ConnectServeur(int msqid,int *Cleclient)
{
dmsgbuf message;
int erreur;
pid_t pid = getpid();

erreur=0;
sprintf(message.txt,"%d",pid);
message.type = CONNECT;
if ((erreur=msgsnd(msqid,&message,L_MSG,message.type)) <0){ /* Envoi un message de type CONNECT contenant le PID du client */
    if (errno==EINTR)
        erreur=0;
    else
        printf("Client:Erreur %d EnvoiMessage:%s %ld\n",errno,message.txt,message.type);
}
printf("Client:Envoi MESSAGE:%s %ld\n",message.txt,message.type);
message.type = pid;
if ((erreur=msgrcv(msqid,&message,L_MSG,message.type,0)) <0){ /* Reception d'un message de type PID contenant la clé client */
    if (errno==EINTR)
        erreur=0;
    else
        printf("Client:Erreur %d EnvoiMessage:%s %ld\n",errno,message.txt,message.type);
}
printf("Client:reception message clé client:%s %ld\n",message.txt,message.type);
sscanf(message.txt,"%d",Cleclient); /* Sauvegarde de la clé client, sscanf est comme un scanf mais l'entrée est le message.txt*/
sprintf(message.txt,"%d",pid); /* Envoi un message de type CONNECT contenant le PID du client*/
message.type = ACK ; /* Acknowledge */
if ((erreur=msgsnd(msqid,&message,L_MSG,message.type)) <0){ /* Envoi un message de type CONNECT contenant le PID du client */
    if (errno==EINTR)
        erreur=0;
    else
        printf("Client:Erreur %d EnvoiMessage:%s %ld\n",errno,message.txt,message.type);
}
printf("Client:Message envoyé :%s %ld\n",message.txt,message.type);

}/* fin procedure */

void DeconnectServeur(int msqid){
    dmsgbuf message;
    int erreur;
    erreur=0;
    while(erreur>=0) {
        sprintf(message.txt,"%d",getpid());
        message.type = DECONNECT;
        if ((erreur=msgsnd(msqid,&message,L_MSG,message.type)) <0){ /* Envoi un message de type CONNECT contenant le PID du client */
            if (errno==EINTR)
            erreur=0;
            else
            printf("Client:Erreur %d EnvoiMessage:%s %ld\n",errno,message.txt,message.type);
        continue ;
        }
        printf("Client:Envoi MESSAGE:%s %ld\n",message.txt,message.type);
    }
}