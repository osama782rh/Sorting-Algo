CC=gcc
CFLAGS=-I. -Wall
DEPS = sorting_algorithms.h
OBJ = main.o sorting_algorithms.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main

.PHONY: clean
