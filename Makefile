NAME := libcs50
VERSION := 8.0.2
UPSTREAM := $(NAME)-$(VERSION)

# installation directory (/usr by default)
DESTDIR ?= /usr

.PHONY: build
build: clean
	$(CC) -c -fPIC -std=gnu99 -Wall -o cs50.o src/cs50.c
	$(CC) -shared -Wl,-soname,libcs50.so.8 -o libcs50.so.$(VERSION) cs50.o
	rm -f cs50.o
	ln -s libcs50.so.$(VERSION) libcs50.so.8
	ln -s libcs50.so.8 libcs50.so
	install -D -m 644 src/cs50.h build/include/cs50.h
	mkdir -p build/lib
	mv libcs50.so* build/lib

.PHONY: install
install: build
	mkdir -p $(DESTDIR)
	cp -r build/* $(DESTDIR)

.PHONY: clean
clean:
	rm -rf build debian/docs/ hackerrank libcs50-* libcs50_*

.PHONY: docs
docs:
	asciidoctor -d manpage -b manpage -D debian/docs/ docs/*.adoc

.PHONY: deb
deb: build docs
	mkdir -p $(UPSTREAM)/usr
	rsync -a build/* $(UPSTREAM)/usr
	tar -cvzf $(NAME)_$(VERSION).orig.tar.gz $(UPSTREAM)
	cp -r debian $(UPSTREAM)
	cd $(UPSTREAM) && debuild -S -sa --lintian-opts --info --display-info --show-overrides

.PHONY: hackerrank
hackerrank:
	rm -rf hackerrank && mkdir -p hackerrank
	cat src/cs50.h > hackerrank/cs50.h
	echo "\n#ifndef _CS50_C\n#define _CS50_C\n" >> hackerrank/cs50.h
	cat src/cs50.c >> hackerrank/cs50.h
	echo "\n#endif" >> hackerrank/cs50.h
