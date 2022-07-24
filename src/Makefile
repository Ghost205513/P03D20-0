CC=gcc

CFLAGS=-Wall -Werror -Wextra -std=c11

all : graph.o stack.o queue.o
	$(CC) graph.o stack.o queue.o -o ./../build/graph -lm
	rm -f *.o

graph.o : graph.c
	$(CC) $(CFLAGS) -c graph.c -o graph.o

stack.o : stack.c
	$(CC) $(CFLAGS) -c stack.c -o stack.o

queue.o : queue.c
	$(CC) $(CFLAGS) -c queue.c -o queue.o

clean :
	rm -f ./../build/Quest_*