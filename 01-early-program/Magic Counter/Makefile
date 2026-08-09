CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: magic_counter

magic_counter: magic_counter.c
	$(CC) $(CFLAGS) -o magic_counter magic_counter.c

clean:
	rm -f magic_counter

.PHONY: all clean
