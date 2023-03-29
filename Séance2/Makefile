# Fichier Makefile

CC = gcc
CFLAGS = -g -Wall -ansi -D _GNU_SOURCE 
CFLAG2 = -c -Wall -ansi -D _GNU_SOURCE 
OBJETS = CL_main.o CL_msg.o CL_mem.o CL_sem.o


all: CL

CL : $(OBJETS)
	$(CC) $(CFLAGS) $(OBJETS) -o CL
	rm -f *~ *.o

CL_main.o : CL_main.c CL_include CL_def.h
	$(CC) $(CFLAG2) CL_main.c -o CL_main.o

CL_msg.o : CL_msg.c CL_include CL_msg.h
	$(CC) $(CFLAG2) CL_msg.c -o CL_msg.o

CL_mem.o : CL_mem.c CL_include CL_mem.h
	$(CC) $(CFLAG2) CL_mem.c -o CL_mem.o

CL_sem.o : CL_sem.c CL_include CL_sem.h
	$(CC) $(CFLAG2) CL_sem.c -o CL_sem.o

clean:
	@rm -f *~ *.o CL 




