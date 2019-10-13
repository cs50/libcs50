VERSION := 10.1.0
MAJOR_VERSION := $(shell echo $(VERSION) | cut -d'.' -f1)

# installation directory (/usr/local by default)
DESTDIR ?= /usr/local
MANDIR ?= share/man/man3

SRC := src/cs50.c
INCLUDE := src/cs50.h
MANS := $(wildcard docs/*.3.gz)

CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11
BASENAME=libcs50
LIB_STATIC=$(BASENAME).a
LIB_OBJ=$(BASENAME).o

OS := $(shell uname)

# Linux
ifeq ($(OS),Linux)
	LIB_BASE := $(BASENAME).so
	LIB_MAJOR := $(BASENAME).so.$(MAJOR_VERSION)
	LIB_VERSION := $(BASENAME).so.$(VERSION)
	LINKER_FLAGS := -Wl,-soname,$(LIB_MAJOR)
# Mac
else ifeq ($(OS),Darwin)
	LIB_BASE := $(BASENAME).dylib
	LIB_MAJOR := $(BASENAME)-$(MAJOR_VERSION).dylib
	LIB_VERSION := $(BASENAME)-$(VERSION).dylib
	LINKER_FLAGS := -Wl,-install_name,$(LIB_VERSION)
endif

LIBS := $(addprefix build/lib/, $(LIB_BASE) $(LIB_MAJOR) $(LIB_VERSION))

.PHONY: all
all: $(LIBS) $(MANS)

$(LIBS): $(SRC) $(INCLUDE) Makefile
	$(CC) $(CFLAGS) -fPIC -shared $(LINKER_FLAGS) -o $(LIB_VERSION) $(SRC)
	$(CC) $(CFLAGS) -c -o $(LIB_OBJ) $(SRC)
	ar rcs $(LIB_STATIC) $(LIB_OBJ)
	chmod 644 $(LIB_STATIC)
	rm -f $(LIB_OBJ)
	ln -sf $(LIB_VERSION) $(LIB_BASE)
	mkdir -p $(addprefix build/, include lib src)
	install -m 644 $(SRC) build/src
	install -m 644 $(INCLUDE) build/include
	mv $(LIB_VERSION) $(LIB_BASE) $(LIB_STATIC) build/lib

.PHONY: install
install: all
	mkdir -p $(addprefix $(DESTDIR)/, src lib include $(MANDIR))
	cp -R $(filter-out deb, $(wildcard build/*)) $(DESTDIR)
	cp -R $(MANS) $(DESTDIR)/$(MANDIR)

ifeq ($(OS),Linux)
	ldconfig $(DESTDIR)/lib
endif

.PHONY: clean
clean:
	rm -rf build

.PHONY: deb
deb: $(LIBS) $(MANS)
	rm -rf build/deb

	# temporary fpm source
	mkdir -p build/deb/$(BASENAME)/usr
	cp -r $(addprefix build/, include lib src) build/deb/$(BASENAME)/usr
	mkdir -p build/deb/$(BASENAME)/usr/share/man/man3
	chmod 755 build/deb/$(BASENAME)/usr/share/man/man3
	cp -r $(MANS) build/deb/$(BASENAME)/usr/share/man/man3
	chmod 644 build/deb/$(BASENAME)/usr/share/man/man3/*
	fpm \
	    --after-install postinst \
	    --after-remove postrm \
	    --category libs \
	    --chdir build/deb/$(BASENAME) \
	    --conflicts lib50-c \
	    --conflicts $(BASENAME) \
	    --conflicts library50-c \
		--deb-no-default-config-files \
	    --deb-priority optional \
	    --description "CS50 library for C" \
	    --input-type dir \
	    --license "MIT" \
	    --maintainer "CS50 <sysadmins@cs50.harvard.edu>" \
	    --name $(BASENAME) \
	    --output-type deb \
	    --package build/deb \
	    --provides lib50-c \
	    --provides $(BASENAME) \
	    --provides library50-c \
	    --replaces lib50-c \
	    --replaces $(BASENAME) \
	    --replaces library50-c \
	    --url https://github.com/cs50/libcs50 \
	    --vendor CS50 \
	    --version $(VERSION) \
	    .

	rm -rf build/deb/$(BASENAME)

rpm: $(LIBS) $(MANS)
	rm -rf build/rpm

	# Temporary fpm source
	mkdir -p build/rpm/$(BASENAME)/usr
	cp -r $(addprefix build/, include lib src) build/rpm/$(BASENAME)/usr
	mkdir -p build/rpm/$(BASENAME)/usr/share/man/man3
	cp -r $(MANS) build/rpm/$(BASENAME)/usr/share/man/man3
	fpm \
	    --after-install post \
	    --after-remove postun \
	    --category libs \
	    --chdir build/rpm/$(BASENAME) \
	    --description "CS50 library for C" \
	    --input-type dir \
	    --license "MIT" \
	    --maintainer "CS50 <sysadmins@cs50.harvard.edu>" \
	    --name $(BASENAME) \
	    --output-type rpm \
	    --package build/rpm \
	    --provides $(BASENAME) \
	    --url https://github.com/cs50/libcs50 \
	    --vendor CS50 \
	    --version $(VERSION) \
	    .

	rm -rf build/rpm/$(BASENAME)

# Used by .travis.yml
.PHONY: version
version:
	@echo $(VERSION)

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)/include/cs50.h
	rm -rf $(DESTDIR)/src/cs50.c
	rm -f $(addprefix $(DESTDIR)/lib/, $(LIB_BASE) $(LIB_MAJOR) $(LIB_VERSION))
	rm -f $(addprefix $(DESTDIR)/$(MANDIR)/, eprintf.3 get_*.3)
