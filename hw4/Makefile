CC=gcc
PROGNAME=memorytest
CLI_ARG= this is a test lets add some more and see how far this bastard will go
ARGS= -I 
WARN= -Wformat-contains-nul
all: execute run
execute: memtest.c
	$(CC) memtest.c -o ${PROGNAME} $(ARGS) $(WARN)
run:
	./${PROGNAME} ${CLI_ARG}