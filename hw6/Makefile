CC=gcc
PROGNAME=sort
SOURCEFILES= sorting.c
CLI_ARG= 1000000
ARGS= -I 
OUTFILE=output.txt

all: compile run
compile: ${SOURCEFILES}
	$(CC) ${SOURCEFILES} -o ${PROGNAME} 
makeList:
	./ytstats.sh
run:
	./${PROGNAME} ${CLI_ARG}
runOut:
	./${PROGNAME} ${CLI_ARG} >> ${OUTFILE}