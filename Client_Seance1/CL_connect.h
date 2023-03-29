#ifndef CL_CONNECT
#define CL_CONNECT

void envoi_connect(int id_mes, int L);
dmsgbuf reception_client(int id_mes, int L);
int cle_client(char* message, int Shm);
void envoi_ack(int id_mes, int L);

#endif
