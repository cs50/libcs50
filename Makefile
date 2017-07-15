VERSION := 8.0.5

# soname - libcs50.so.<major_version>
SONAME := libcs50.so.$(shell echo $(VERSION) | head -c 1)

# installation directory (/usr/local by default)
DESTDIR ?= /usr/local

.PHONY: build
build: clean
	$(CC) -c -fPIC -std=c99 -Wall -o cs50.o src/cs50.c
	$(CC) -shared -Wl,-soname,$(SONAME) -o libcs50.so.$(VERSION) cs50.o
	rm -f cs50.o
	ln -s libcs50.so.$(VERSION) $(SONAME)
	ln -s $(SONAME) libcs50.so
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

# requires asciidoctor (gem install asciidoctor)
.PHONY: docs
docs:
	asciidoctor -d manpage -b manpage -D debian/docs/ docs/*.adoc

.PHONY: deb
deb: build docs
	@echo "libcs50 ($(VERSION)-0ubuntu1) trusty; urgency=low" > debian/changelog
	@echo "  * v$(VERSION)" >> debian/changelog
	@echo " -- CS50 Sysadmins <sysadmins@cs50.harvard.edu>  $$(date --rfc-2822)" >> debian/changelog
	mkdir -p libcs50-$(VERSION)/usr
	rsync -a build/* libcs50-$(VERSION)/usr --exclude=hack
	tar -cvzf libcs50_$(VERSION).orig.tar.gz libcs50-$(VERSION)
	cp -r debian libcs50-$(VERSION)
	cd libcs50-$(VERSION) && debuild -S -sa --lintian-opts --display-info --info --show-overrides
	mkdir -p build/deb
	mv libcs50-* libcs50_* build/deb

.PHONY: hack
hack:
	rm -rf build/hack && mkdir -p build/hack
	cat src/cs50.h > build/hack/cs50.h
	echo "\n#ifndef _CS50_C\n#define _CS50_C\n" >> build/hack/cs50.h
	cat src/cs50.c >> build/hack/cs50.h
	echo "\n#endif" >> build/hack/cs50.h

# used by .travis.yml
.PHONY: version
version:
	@echo $(VERSION)
