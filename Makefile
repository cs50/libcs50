DESCRIPTION = CS50 Library for C
MAINTAINER = CS50 <sysadmins@cs50.harvard.edu>
NAME = lib50-c
OLD_NAME = library50-c
VERSION = 7.0.0

CC=clang
CFLAGS=-Wall -Werror -std=c99
INCDIRS = -I./build/usr/include
LIBDIRS=-L./build/usr/lib
LDFLAGS=-lcs50
DEBUG=-O0 -ggdb3

# Create test build. 
# Accepts three arguments: input file, output file, additoinal compiler flags (optional)
cc-test = $(CC) $(DEBUG) $(CFLAGS) $(INCDIRS) $(3) $(1) -o $(2) $(LIBDIRS) $(LDFLAGS)

TESTDIRS=$(sort $(dir $(wildcard ./tests/*/*/)))
TESTS=$(addsuffix test, $(TESTDIRS))

.PHONY: bash
bash:
	docker run -i --rm -t -v "$(PWD):/root" cs50/cli

.PHONY: build
build: clean Makefile src/cs50.c src/cs50.h
	mkdir -p build/usr/include build/usr/lib build/usr/src
	$(CC) $(CFLAGS) -c -fPIC -o build/cs50.o src/cs50.c
	$(CC) -o build/usr/lib/libcs50.so -shared build/cs50.o
	rm -f build/cs50.o
	cp src/cs50.h build/usr/include
	cp src/cs50.c build/usr/src
	find build -type d -exec chmod 0755 {} +
	find build -type f -exec chmod 0644 {} +

.PHONY: clean
clean:
	rm -rf build
	rm -f $(TESTS)

.PHONY: deb
deb: build
	fpm \
	-C build \
	-m "$(MAINTAINER)" \
	-n "$(NAME)" \
	-p build \
	-s dir \
	-t deb \
	-v $(VERSION) \
	--conflicts "$(NAME) (<< $(VERSION))" \
	--conflicts $(OLD_NAME) \
	--deb-no-default-config-files \
	--depends c-compiler \
	--description "$(DESCRIPTION)" \
	--provides $(NAME) \
	--provides $(OLD_NAME) \
	--replaces "$(NAME) (<= $(VERSION))" \
	--replaces $(OLD_NAME) \
	usr

.PHONY: hackerrank
hackerrank: build
	cat src/cs50.h > build/cs50.h
	echo "\n#ifndef _CS50_C\n#define _CS50_C\n" >> build/cs50.h
	cat src/cs50.c >> build/cs50.h
	echo "\n#endif" >> build/cs50.h

# TODO: add dependencies
.PHONY: pacman
pacman: build
	rm -f $(NAME)-$(VERSION)-*.pkg.tar.xz
	fpm \
	-C build \
	-m "$(MAINTAINER)" \
	-n "$(NAME)" \
	-p build \
	-s dir \
	-t pacman \
	-v $(VERSION) \
	--description "$(DESCRIPTION)" \
	usr

# TODO: add dependencies
.PHONY: rpm
rpm: build
	rm -f $(NAME)-$(VERSION)-*.rpm
	fpm \
	-C build \
	-m "$(MAINTAINER)" \
	-n "$(NAME)" \
	-p build \
	-s dir \
	-t rpm \
	-v $(VERSION) \
	--description "$(DESCRIPTION)" \
	usr

# TODO: Improve test suite
.PHONY: test
test: build hackerrank test_driver
	cd tests; ./test_driver
	$(call cc-test, tests/eprintf.c, build/eprintf, -Wno-deprecated-declarations)
	LD_LIBRARY_PATH=build/usr/lib build/eprintf
	clang -Ibuild -std=c11 -Wall -Werror -Wno-deprecated-declarations tests/hackerrank.c -o build/hackerrank
	build/hackerrank

.PHONY: test_driver
test_driver: $(TESTS)
	$(call cc-test, tests/test_driver.c, tests/test_driver)

tests/%/test: tests/%/test.c build
	$(call cc-test, $<, $@)
