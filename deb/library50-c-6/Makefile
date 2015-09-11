prefix = /usr/local
srcdir = $(prefix)/src
libdir = $(prefix)/lib
includedir = $(prefix)/include

CFLAGS = -lm --std=c99

all:
	gcc -c -o cs50.o cs50.c
	ar rcs libcs50.a cs50.o

clean:
	rm -f libcs50.a cs50.o

install: all
	install -m 0644 libcs50.a $(DESTDIR)$(libdir)
	install -m 0644 cs50.h $(DESTDIR)$(includedir)
	install -m 0644 cs50.c $(DESTDIR)$(srcdir)
