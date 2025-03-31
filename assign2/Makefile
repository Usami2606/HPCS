CC = gcc
CFLAGS = -fopenmp -Wall -O2

all: sum1

sum1: sum1.o timer.o
	$(CC) $(CFLAGS) -o sum1 sum1.o timer.o

sum1.o: sum1.c
	$(CC) $(CFLAGS) -c sum1.c

timer.o: timer.c
	$(CC) $(CFLAGS) -c timer.c

clean:
	rm -f sum1 sum1.o timer.o