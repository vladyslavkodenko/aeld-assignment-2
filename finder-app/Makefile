CC = $(CROSS_COMPILE)gcc

CFLAGS ?= -Wall -Werror -g

all: writer

writer: writer.o
	$(CC) $(CFLAGS) -o $@ $^

writer.o: writer.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -f writer *.o