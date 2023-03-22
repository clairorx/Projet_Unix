# Fichier Makefile

CC = gcc
CFLAGS = -g -Wall -ansi -D _GNU_SOURCE 
CFLAG2 = -c -Wall -ansi -D _GNU_SOURCE 
OBJETS = CL_main.o CL_msg.o CL_connect.o

all: cl CL

cl : $(OBJETS) CL.c
	$(CC) $(CFLAGS) $(OBJETS) -o cl_zz
	$(CC) $(FLAGS) CL.c -o CL

CL_msg.o : CL_msg.c CL_include CL_msg.h
	$(CC) $(CFLAG2) CL_msg.c -o CL_msg.o

CL_connect.o : CL_connect.c CL_include CL_connect.h
	$(CC) $(CFLAG2) CL_connect.c -o CL_connect.o
clean:
	@rm -f *~ *.o cl_zz CL





