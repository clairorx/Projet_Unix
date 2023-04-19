# Fichier Makefile

CC = gcc
CFLAGS = -g -Wall -ansi -D _SVID_SOURCE
CFLAG2 = -c -Wall -ansi -D _GNU_SOURCE 
OBJETS = CL.o 

CL : $(OBJETS) CL.c CL_include CL_def.h 
	$(CC) $(CFLAGS) $(OBJETS) -o CL_zz
	$(CC) $(CFLAGS) CL.c -o CL


clean:
	@rm -f *~ *.o CL_zz CL 




