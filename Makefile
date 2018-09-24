VERSION := 8.1.1
MAJOR_VERSION := $(shell echo $(VERSION) | head -c 1)

# installation directory (/usr/local by default)
DESTDIR ?= /usr/local
MANDIR ?= share/man/man3

SRC := src/cs50.c
INCLUDE := src/cs50.h
MANS := $(wildcard docs/*.3)

CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

OS := $(shell uname)

# Linux
ifeq ($(OS),Linux)
	LIB_BASE := libcs50.so
	LIB_MAJOR := libcs50.so.$(MAJOR_VERSION)
	LIB_VERSION := libcs50.so.$(VERSION)
	LINKER_FLAGS := -Wl,-soname,$(LIB_VERSION)
# Mac
else ifeq ($(OS),Darwin)
	LIB_BASE := libcs50.dylib
	LIB_MAJOR := libcs50-$(MAJOR_VERSION).dylib
	LIB_VERSION := libcs50-$(VERSION).dylib
	LINKER_FLAGS := -Wl,-install_name,$(LIB_VERSION)
endif

LIBS := $(addprefix build/lib/, $(LIB_BASE) $(LIB_MAJOR) $(LIB_VERSION))

.PHONY: all
all: $(LIBS) $(MANS)

$(LIBS): $(SRC) $(INCLUDE) Makefile
	$(CC) $(CFLAGS) -fPIC -shared $(LINKER_FLAGS) -o $(LIB_VERSION) $(SRC)
	ln -s $(LIB_VERSION) $(LIB_MAJOR)
	ln -s $(LIB_MAJOR) $(LIB_BASE)
	mkdir -p $(addprefix build/, include lib src)
	install -m 644 $(SRC) build/src
	install -m 644 $(INCLUDE) build/include
	mv $(LIB_VERSION) $(LIB_MAJOR) $(LIB_BASE) build/lib

.PHONY: install
install: all
	mkdir -p $(addprefix $(DESTDIR)/, src lib include $(MANDIR))
	cp -r $(filter-out deb, $(wildcard build/*)) $(DESTDIR)
	cp -r $(MANS) $(DESTDIR)/$(MANDIR)

ifeq ($(OS),Linux)
	ldconfig
endif

.PHONY: clean
clean:
	rm -rf build

.PHONY: deb
deb: $(LIBS) $(MANS)
	rm -rf build/deb

	# temporary fpm source
	mkdir -p build/deb/libcs50/usr/local
	cp -r $(addprefix build/, include lib src) build/deb/libcs50/usr/local
	mkdir -p build/deb/libcs50/usr/local/share/man/man3
	cp -r $(MANS) build/deb/libcs50/usr/local/share/man/man3
	fpm \
	    --after-install postinst \
	    --after-remove postrm \
	    --category libs \
	    --chdir build/deb/libcs50 \
	    --conflicts lib50-c \
	    --conflicts libcs50 \
	    --conflicts library50-c \
	    --deb-priority optional \
	    --description "CS50 library for C" \
	    --input-type dir \
	    --license "MIT" \
	    --maintainer "CS50 <sysadmins@cs50.harvard.edu>" \
	    --name libcs50 \
	    --output-type deb \
	    --package build/deb \
	    --provides lib50-c \
	    --provides libcs50 \
	    --provides library50-c \
	    --replaces lib50-c \
	    --replaces libcs50 \
	    --replaces library50-c \
	    --url https://github.com/cs50/libcs50 \
	    --vendor CS50 \
	    --version $(VERSION) \
	    .

	rm -rf build/deb/libcs50

rpm: $(LIBS) $(MANS)
	rm -rf build/rpm

	# temporary fpm source
	mkdir -p build/rpm/libcs50/usr/local
	cp -r $(addprefix build/, include lib src) build/rpm/libcs50/usr/local
	mkdir -p build/rpm/libcs50/usr/local/share/man/man3
	cp -r $(MANS) build/rpm/libcs50/usr/local/share/man/man3
	fpm \
	    --after-install post \
	    --after-remove postun \
	    --category libs \
	    --chdir build/rpm/libcs50 \
	    --description "CS50 library for C" \
	    --input-type dir \
	    --license "MIT" \
	    --maintainer "CS50 <sysadmins@cs50.harvard.edu>" \
	    --name libcs50 \
	    --output-type rpm \
	    --package build/rpm \
	    --provides libcs50 \
	    --url https://github.com/cs50/libcs50 \
	    --vendor CS50 \
	    --version $(VERSION) \
	    .

	rm -rf build/rpm/libcs50

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
