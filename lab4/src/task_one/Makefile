CC=gcc
CFLAGS=-std=c99

all: parallel_min_max

utils.o: utils.h
	$(CC) -o utils.o -c $(CFLAGS) utils.c

find_min_max.o: utils.h find_min_max.h
	$(CC) -o find_min_max.o -c $(CFLAGS) find_min_max.c

parallel_min_max: utils.h find_min_max.h utils.o find_min_max.o
	$(CC) -o parallel_min_max utils.o find_min_max.o $(CFLAGS) parallel_min_max.c

clean:
	rm *.o
