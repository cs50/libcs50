prefix = /usr/local
srcdir = $(prefix)/src
libdir = $(prefix)/lib
includedir = $(prefix)/include

CFLAGS = --std=c99

all:
	gcc -c -ggdb3 -O0 -fPIC -o cs50.o cs50.c
	gcc -shared -o libcs50.so cs50.o

clean:
	rm -f libcs50.so cs50.o

install: all
	install -m 0644 libcs50.so $(DESTDIR)$(libdir)
	install -m 0644 cs50.h $(DESTDIR)$(includedir)
	install -m 0644 cs50.c $(DESTDIR)$(srcdir)
