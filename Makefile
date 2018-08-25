CC=gcc
CFLAGS=-Wall -O3

faststats: faststats-cli.o faststats.o
	$(CC) -o $@ $^

faststats-cli.o: faststats-cli.c faststats.h
	$(CC) $(CFLAGS) -c -o faststats-cli.o faststats-cli.c

faststats.o: faststats.c faststats.h
	$(CC) $(CFLAGS) -c -o faststats.o faststats.c

clean:
	rm -f faststats faststats-cli.o faststats.o

.PHONY: clean
