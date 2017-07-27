VERSION := 8.0.6
MAJOR_VERSION := $(shell echo $(VERSION) | head -c 1)

# installation directory (/usr/local by default)
DESTDIR ?= /usr/local
MANDIR ?= share/man/man3

SRC := src/cs50.c
INCLUDE := src/cs50.h
DOCS := $(wildcard docs/*.adoc)
MANS := $(addprefix debian/, $(DOCS:%.adoc=%.3))

CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

OS := $(shell uname)
# Linux
ifeq ($(OS),Linux)
	LIB_BASE := libcs50.so
	LIB_MAJOR := libcs50.so.$(MAJOR_VERSION)
	LIB_VERSION := libcs50.so.$(VERSION)
	LINKER_FLAGS := -Wl,-soname,$(LIB_MAJOR)
# Mac
else ifeq ($(OS),Darwin)
	LIB_BASE := libcs50.dylib
	LIB_MAJOR := libcs50-$(MAJOR_VERSION).dylib
	LIB_VERSION := libcs50-$(VERSION).dylib
	LINKER_FLAGS := -Wl,-install_name,$(LIB_MAJOR)
endif

LIBS := $(addprefix build/lib/, $(LIB_BASE) $(LIB_MAJOR) $(LIB_VERSION))

.PHONY: all
all: $(LIBS) $(MANS)

$(LIBS): $(SRC) $(INCLUDE) Makefile
	$(CC) $(CFLAGS) -fPIC -shared $(LINKER_FLAGS) -o $(LIB_VERSION) $(SRC)
	ln -s $(LIB_VERSION) $(LIB_MAJOR)
	ln -s $(LIB_MAJOR) $(LIB_BASE)
	mkdir -p src build/include
	install -m 644 src/cs50.h build/include/cs50.h
	mkdir -p build/lib build/src/libcs50
	mv $(LIB_VERSION) $(LIB_MAJOR) $(LIB_BASE) build/lib
	cp -r $(SRC) $(INCLUDE) build/src/libcs50

.PHONY: install
install: all
	mkdir -p $(addprefix $(DESTDIR)/, src lib include $(MANDIR))
	cp -r build/* $(DESTDIR)
	cp debian/docs/* $(DESTDIR)/$(MANDIR)
ifeq ($(OS),Linux)
	ldconfig
endif

.PHONY: clean
clean:
	rm -rf build debian/docs/

# requires asciidoctor (gem install asciidoctor)
$(MANS): $(DOCS) Makefile
	asciidoctor -d manpage -b manpage -D debian/docs/ $(DOCS)

.PHONY: deb
deb: $(LIBS) $(MANS)
	rm -rf build/deb &>/dev/null
	@echo "libcs50 ($(VERSION)-0ubuntu$(DIST_VERSION)) $(DIST); urgency=low" > debian/changelog
	@echo "  * v$(VERSION)" >> debian/changelog
	@echo " -- CS50 Sysadmins <sysadmins@cs50.harvard.edu>  $$(date --rfc-2822)" >> debian/changelog
	mkdir -p libcs50-$(VERSION)/usr
	cp -r build/* libcs50-$(VERSION)/usr
	GZIP=-n tar --mtime='1970-01-01' -cvzf libcs50_$(VERSION).orig.tar.gz libcs50-$(VERSION)
	cp -r debian libcs50-$(VERSION)
	cd libcs50-$(VERSION) && debuild $(SIGNING_OPTS) -S -sa --lintian-opts --display-info --info --show-overrides
	mkdir -p build/deb
	mv libcs50-* libcs50_* build/deb

.PHONY: hack
hack:
	mkdir -p build/hack
	echo "\n#ifndef _CS50_C\n#define _CS50_C\ntypedef char *string;\n" > build/hack/cs50.h
	grep -v '^#include "cs50.h"' src/cs50.c >> build/hack/cs50.h
	echo "\n#endif" >> build/hack/cs50.h
	cat src/cs50.h >> build/hack/cs50.h

# used by .travis.yml
.PHONY: version
version:
	@echo $(VERSION)

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)/include/cs50.h
	rm -rf $(DESTDIR)/src/libcs50
	rm -f $(addprefix $(DESTDIR)/lib/, $(LIB_BASE) $(LIB_MAJOR) $(LIB_VERSION))
	rm -f $(addprefix $(DESTDIR)/$(MANDIR)/, eprintf.3 get_*.3)
