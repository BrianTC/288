CC=gcc
PROGNAME=linkedList
SOURCEFILES= llist.c
CLI_ARG= stats.csv
ARGS= -I 
OUTFILE=output.txt

all: compile run runOut
compile: ${SOURCEFILES}
	$(CC) ${SOURCEFILES} -o ${PROGNAME} 
makeList:
	./ytstats.sh
run:
	./${PROGNAME} ${CLI_ARG}
runBig:
	./${PROGNAME} big_stats.csv
runOut:
	./${PROGNAME} ${CLI_ARG} > ${OUTFILE}