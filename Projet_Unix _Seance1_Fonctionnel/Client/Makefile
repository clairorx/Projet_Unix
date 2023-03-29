# Fichier Makefile

CC = gcc
CFLAGS = -g -Wall -ansi -D _GNU_SOURCE 
CFLAG2 = -c -Wall -ansi -D _GNU_SOURCE 
OBJETS = CL_main.o CL_msg.o CL_connect.o CL_mem.o CL_data.o CL_sem.o

all: cl CL

cl : $(OBJETS) CL.c
	$(CC) $(CFLAGS) $(OBJETS) -o cl_zz
	$(CC) $(FLAGS) CL.c -o CL

CL_msg.o : CL_msg.c CL_include CL_msg.h
	$(CC) $(CFLAG2) CL_msg.c -o CL_msg.o

CL_connect.o : CL_connect.c CL_include CL_connect.h
	$(CC) $(CFLAG2) CL_connect.c -o CL_connect.o

CL_mem.o : CL_mem.c CL_include CL_mem.h
	$(CC) $(CFLAG2) CL_mem.c -o CL_mem.o

CL_data.o : CL_data.c CL_include CL_data.h
	$(CC) $(CFLAG2) CL_data.c -o CL_data.o

CL_sem.o : CL_sem.c CL_include CL_sem.h
	$(CC) $(CFLAG2) CL_sem.c -o CL_sem.o
clean:
	@rm -f *~ *.o cl_zz CL





