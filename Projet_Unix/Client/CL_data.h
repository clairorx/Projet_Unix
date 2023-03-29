/**********************************************************
*						  	  *
*		       Fichier CL_data.h                   *
*							  *
**********************************************************/

/**
 * @brief Fonction qui permet de lire les données dans la mémoire partagée
 * 
 * @param shmid 
 * @param MemBuf 
 */
void read_data(int shmid, BUF **MemBuf);