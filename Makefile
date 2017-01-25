# useful paths
SRC_DIR = src
HDR = $(SRC_DIR)/cs50.h
SRC = $(SRC_DIR)/cs50.c

BUILD_DIR = build
OBJ = $(BUILD_DIR)/cs50.o
USR_DIR = $(BUILD_DIR)/usr
INCLUDE_DIR = $(USR_DIR)/include
LIB_DIR = $(USR_DIR)/lib
MAN_DIR = $(USR_DIR)/share/man/man3
BUILD_SRC = $(USR_DIR)/src

# eprintf
EPRINTF_EXE = $(BUILD_DIR)/eprintf

# HackerRank
HR_HDR = $(BUILD_DIR)/cs50.h
HR_EXE = $(BUILD_DIR)/hackerrank

TESTS_DIR = tests

# deb package info
DESCRIPTION = CS50 Library for C
MAINTAINER = CS50 <sysadmins@cs50.harvard.edu>
NAME = lib50-c
OLD_NAME = library50-c
VERSION = 7.1.2

.PHONY: bash
bash:
	docker run -i --rm -t -v "$(PWD):/root" cs50/cli

.PHONY: build
build: clean Makefile $(SRC) $(HDR)
	mkdir -p "$(INCLUDE_DIR)" "$(LIB_DIR)" "$(MAN_DIR)" "$(BUILD_SRC)"
	gcc -c -fPIC -std=c99 -Wall -Werror -o "$(OBJ)" "$(SRC)"
	gcc -o "$(LIB_DIR)/libcs50.so" -shared "$(OBJ)"
	rm -f "$(OBJ)"
	cp "$(HDR)" "$(INCLUDE_DIR)"
	cp "$(SRC)" "$(BUILD_SRC)"
	cp -r docs/* "$(MAN_DIR)"
	find "$(BUILD_DIR)" -type d -exec chmod 0755 {} +
	find "$(BUILD_DIR)" -type f -exec chmod 0644 {} +

.PHONY: clean
clean:
	rm -rf "$(BUILD_DIR)"

.PHONY: deb
deb: build
	fpm \
	-C "$(BUILD_DIR)" \
	-m "$(MAINTAINER)" \
	-n "$(NAME)" \
	-p "$(BUILD_DIR)" \
	-s dir \
	-t deb \
	-v "$(VERSION)" \
	--conflicts "$(NAME) (<< $(VERSION))" \
	--conflicts "$(OLD_NAME)" \
	--deb-no-default-config-files \
	--depends c-compiler \
	--description "$(DESCRIPTION)" \
	--provides "$(NAME)" \
	--provides "$(OLD_NAME)" \
	--replaces "$(NAME) (<= $(VERSION))" \
	--replaces "$(OLD_NAME)" \
	usr

.PHONY: hackerrank
hackerrank: build
	cat "$(HDR)" > "$(HR_HDR)"
	echo "\n#ifndef _CS50_C\n#define _CS50_C\n" >> "$(HR_HDR)"
	cat "$(SRC)" >> "$(HR_HDR)"
	echo "\n#endif" >> "$(HR_HDR)"

.PHONY: install
install: build
	cp "$(INCLUDE_DIR)"/* /usr/include
	cp "$(LIB_DIR)"/* /usr/lib

# TODO: add dependencies
.PHONY: pacman
pacman: build
	rm -f "$(NAME)-$(VERSION)-"*.pkg.tar.xz
	fpm \
	-C "$(BUILD_DIR)" \
	-m "$(MAINTAINER)" \
	-n "$(NAME)" \
	-p "$(BUILD_DIR)" \
	-s dir \
	-t pacman \
	-v "$(VERSION)" \
	--description "$(DESCRIPTION)" \
	usr

# TODO: add dependencies
.PHONY: rpm
rpm: build
	rm -f "$(NAME)-$(VERSION)-"*.rpm
	fpm \
	-C "$(BUILD_DIR)" \
	-m "$(MAINTAINER)" \
	-n "$(NAME)" \
	-p "$(BUILD_DIR)" \
	-s dir \
	-t rpm \
	-v "$(VERSION)" \
	--description "$(DESCRIPTION)" \
	usr

# TODO: improve test suite
.PHONY: test
test: build hackerrank
	clang -ggdb3 -I "$(INCLUDE_DIR)" -O0 -std=c99 -Wall -Werror -Wno-deprecated-declarations "$(TESTS_DIR)/eprintf.c" -L "$(LIB_DIR)" -lcs50 -o "$(EPRINTF_EXE)"
	clang -I "$(BUILD_DIR)" -std=c99 -Wall -Werror -Wno-deprecated-declarations "$(TESTS_DIR)/hackerrank.c" -o "$(HR_EXE)"
	LD_LIBRARY_PATH="$(LIB_DIR)" "$(EPRINTF_EXE)"
	"$(HR_EXE)"
