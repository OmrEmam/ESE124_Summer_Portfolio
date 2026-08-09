CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic

all: brobank
brobank: main.c brobank.c adt.c brobank.h adt.h
	$(CC) $(CFLAGS) main.c brobank.c adt.c -o brobank

clean:
	rm -f brobank

.PHONY: all clean
