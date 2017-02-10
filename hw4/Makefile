CC=gcc
PROGNAME=memorytest
CLI_ARG= this is a test
ARGS= -I 
WARN= -Wformat-contains-nul
all: execute run
execute: memtest.c
	$(CC) memtest.c -o ${PROGNAME} $(ARGS) $(WARN)
run:
	./${PROGNAME} ${CLI_ARG}