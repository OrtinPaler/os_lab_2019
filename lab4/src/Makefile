CC=gcc
CFLAGS=-std=c99

all: process_memory parallel_sum

process_memory:
	$(CC) $(CFLAGS) process_memory.c -o process_memory

utils.o: task_one/utils.h
	$(CC) -o utils.o -c -std=c99 task_one/utils.c

parallel_sum: task_one/utils.h utils.o
	$(CC) -o parallel_sum utils.o -lpthread $(CFLAGS) parallel_sum.c

clean:
	rm *.o parallel_sum process_memory