CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS += -Wmissing-prototypes -Wno-unused-parameter
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
CC     = gcc

all: lex

lex: lex.c lex.h config.h Makefile
	$(CC) -O3 $(CFLAGS) -o $@ $< -lX11 $(LDFLAGS)

install: all
	install -Dm755 lex $(DESTDIR)$(BINDIR)/lex

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/lex

clean:
	rm -f lex *.o

.PHONY: all install uninstall clean
