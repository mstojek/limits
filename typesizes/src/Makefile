CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2
LDFLAGS ?=

all: typesizes

typesizes: typesizes.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f typesizes *.o

.PHONY: all clean
