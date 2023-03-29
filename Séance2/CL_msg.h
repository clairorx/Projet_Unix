#ifndef CL_MSG
#define CL_MSG

key_t connect_messagerie(char* CleServ, int Msg);
void envoi_connect(int id_mes, int L);
dmsgbuf reception_client(int id_mes, int L);
int cle_client(char* message, int Shm);
void envoi_ack(int id_mes, int L);
void envoi_deconnect(int id_mes, int L);


#endif
