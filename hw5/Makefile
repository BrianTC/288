CC=gcc
PROGNAME=linkedList
SOURCEFILES= llist.c
CLI_ARG= stats.csv
ARGS= -I 
WARN= -Wformat-contains-nul
all: execute run
execute: ${SOURCEFILES}
	$(CC) ${SOURCEFILES} -o ${PROGNAME} $(ARGS) $(WARN)
run:
	./${PROGNAME} ${CLI_ARG}