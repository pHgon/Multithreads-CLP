CC=gcc

CFLAGS=-g -O1 -std=c99 -Wall -Werror -Wextra -Wno-unused-parameter -pthread -fopenmp
CFLAGS=-g -O1 -std=c99 -Wall -pthread -fopenmp
LDFLAGS=-lm 

all: grade clean

bucket_pthreads.o: bucket_pthreads.c

bucket_openMP.o: bucket_openMP.c

main.o: main.c

main: bucket_pthreads.o bucket_openMP.o main.o
	$(CC) $(CFLAGS) bucket_pthreads.o bucket_openMP.o main.o -o main $(LDFLAGS)

grade: main
	@./main

clean:
	@rm -rf *.o main