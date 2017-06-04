NAME := libcs50
VERSION := 8.0.2
UPSTREAM := $(NAME)-$(VERSION)

# installation directory (/usr/local by default)
DESTDIR ?= /usr/local

.PHONY: build
build: clean
	$(CC) -c -fPIC -std=gnu99 -Wall -o cs50.o src/cs50.c
	$(CC) -shared -Wl,-soname,libcs50.so.8 -o libcs50.so.$(VERSION) cs50.o
	rm -f cs50.o
	ln -s libcs50.so.$(VERSION) libcs50.so.8
	ln -s libcs50.so.8 libcs50.so
	install -D -m 644 src/cs50.h build/include/cs50.h
	mkdir -p build/lib build/src/libcs50
	mv libcs50.so* build/lib
	cp -r src/* build/src/libcs50

.PHONY: install
install: build docs
	mkdir -p $(DESTDIR) $(DESTDIR)/share/man/man3
	cp -r build/* $(DESTDIR)
	cp -r debian/docs/* $(DESTDIR)/share/man/man3

.PHONY: clean
clean:
	rm -rf build debian/docs/ libcs50-* libcs50_*

.PHONY: docs
docs:
	asciidoctor -d manpage -b manpage -D debian/docs/ docs/*.adoc

.PHONY: deb
deb: build docs
	mkdir -p $(UPSTREAM)/usr
	rsync -a build/* $(UPSTREAM)/usr --exclude=hack
	tar -cvzf $(NAME)_$(VERSION).orig.tar.gz $(UPSTREAM)
	cp -r debian $(UPSTREAM)
	cd $(UPSTREAM) && debuild -S -sa --lintian-opts --info --display-info --show-overrides
	mkdir -p build/deb
	mv libcs50-* libcs50_* build/deb
.PHONY: hack
hack:
	rm -rf build/hack && mkdir -p build/hack
	cat src/cs50.h > build/hack/cs50.h
	echo "\n#ifndef _CS50_C\n#define _CS50_C\n" >> build/hack/cs50.h
	cat src/cs50.c >> build/hack/cs50.h
	echo "\n#endif" >> build/hack/cs50.h
