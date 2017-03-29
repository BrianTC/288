CC=gcc
SRC=search.c
CLI=-g
RUN_ARGS=1 2 3 4 5 6 7 8 9 10 11 12 0 13 14 15 dfs
#{dfs|bfs|astar} Algorithim Choices
PROG_NAME=puzzle

all:	compile    run
compile:
	$(CC) $(CLI) $(SRC) -o $(PROG_NAME)
run:
	./$(PROG_NAME) $(RUN_ARGS)