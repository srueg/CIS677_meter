CC=gcc
CFLAGS= -Wall -g -std=c99

ODIR=obj

meter: *.c
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f meter
	