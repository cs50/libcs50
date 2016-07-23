src = ../../src

prefix = /usr/local
includedir = $(prefix)/include
libdir = $(prefix)/lib
srcdir = $(prefix)/src

CFLAGS = --std=c99

all:
	gcc -c -I$(src) -o cs50.o $(src)/cs50.c
	ar rcs libcs50.a cs50.o

clean:
	rm -f libcs50.a cs50.o
	dh_clean

install: all
	install -D -m 0644 libcs50.a $(DESTDIR)$(libdir)/libcs50.a
	install -D -m 0644 $(src)/cs50.h $(DESTDIR)$(includedir)/cs50.h
	install -D -m 0644 $(src)/cs50.c $(DESTDIR)$(srcdir)/cs50.c
