CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2
LDFLAGS ?=

all: limits

limits: limits.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f limits *.o

.PHONY: all clean
