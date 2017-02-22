CC=gcc
PROGNAME=linkedList
SOURCEFILES= llist.c
CLI_ARG= stats.csv
ARGS= -I 
WARN= #-Wformat-contains-nul $(WARN)s
all: execute run
execute: ${SOURCEFILES}
	$(CC) ${SOURCEFILES} -o ${PROGNAME} 
run:
	./${PROGNAME} ${CLI_ARG}