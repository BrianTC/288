CC=gcc
PROGNAME=memorytest
CLI_ARG= the quick brown fox jumped over the lazy dog
ARGS= -I 
WARN= -Wformat-contains-nul
all: execute run
execute: memtest.c
	$(CC) memtest.c -o ${PROGNAME} $(ARGS) $(WARN)
run:
	./${PROGNAME} ${CLI_ARG}