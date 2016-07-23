PACKAGE_NAME = library50-c
VERSION = 6.0.0
SRC_DIR = ./src
PREFIX = /usr/local
DEB_FILE = $(PACKAGE_NAME)_$(VERSION)_amd64.deb

all: lib deb test

build:
	rm -rf build
	mkdir build
	clang -c -std=c99 -Wall -Werror -o build/cs50.o src/cs50.c

lib: build
	rm -rf lib
	mkdir lib
	ar rcs lib/libcs50.a build/cs50.o

deb: lib
	fpm -n $(PACKAGE_NAME) -v $(VERSION) --provides $(PACKAGE_NAME) \
		--vendor CS50 -m "CS50 <sysadmins@cs50.harvard.edu>" \
		--category misc -a amd64 --no-depends \
		--description "$$(printf "CS50 library for C\nSimplifies user input for C.\n")" \
		--url https://mirror.cs50.net/library50/c/ \
		--after-install deb/postinst \
		--deb-changelog deb/changelog \
		--deb-no-default-config-files \
		-s dir -t deb \
		./lib/libcs50.a=$(PREFIX)/lib/libcs50.a $(SRC_DIR)/cs50.c=$(PREFIX)/src/cs50.c $(SRC_DIR)/cs50.h=$(PREFIX)/include/cs50.h

	mv $(DEB_FILE) deb/
test: lib
	clang -ggdb3 -Isrc -O0 -std=c99 -Wall -Werror -Wno-deprecated-declarations tests/test.c -Llib -lcs50 -o build/test

clean:
	rm -rf build/ lib/
	rm -f $(DEB_FILE)
