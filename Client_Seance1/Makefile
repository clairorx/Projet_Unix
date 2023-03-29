#**********************************************************
#						  	  *
#             	     Fichier Makefile                     *
#							  *
#**********************************************************

CC = gcc
CFLAGS = -g -Wall -ansi -D _GNU_SOURCE 
CFLAG2 = -c -Wall -ansi -D _GNU_SOURCE 
OBJETS = CL_main.o CL_msg.o CL_mem.o CL_connect.o

all: cl CL

cl : $(OBJETS) CL.c
	$(CC) $(CFLAGS) $(OBJETS) -o cl_zz
	$(CC) $(CFLAGS) CL.c -o CL

CL_main.o : CL_main.c CL_include
	$(CC) $(CFLAG2) CL_main.c -o CL_main.o

CL_msg.o : CL_msg.c CL_include CL_msg.h
	$(CC) $(CFLAG2) CL_msg.c -o CL_msg.o

CL_mem.o : CL_mem.c CL_include CL_mem.h
	$(CC) $(CFLAG2) CL_mem.c -o CL_mem.o

CL_connect.o : CL_connect.c CL_include CL_connect.h
	$(CC) $(CFLAG2) CL_connect.c -o CL_connect.o

clean:
	@rm -f *~ *.o cl_zz CL 




