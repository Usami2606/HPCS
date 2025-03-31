CC = gcc
CFLAGS = -fopenmp -Wall -O2

all: main

main: main.o sum1.o timer.o
	$(CC) $(CFLAGS) -o main main.o sum1.o timer.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

sum1.o: sum1.c
	$(CC) $(CFLAGS) -c sum1.c

timer.o: timer.c
	$(CC) $(CFLAGS) -c timer.c

clean:
	rm -f main main.o sum1.o timer.o
