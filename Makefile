DESCRIPTION = CS50 Library for C
MAINTAINER = CS50 <sysadmins@cs50.harvard.edu>
NAME = lib50-c
VERSION = 7.0.0

.PHONY: bash
bash:
	docker run -i --rm -t -v "$(PWD):/root" cs50/cli

.PHONY: build
build: clean Makefile src/cs50.c src/cs50.h
	mkdir -p build/usr/include build/usr/lib build/usr/src
	gcc -c -fPIC -std=c99 -Wall -Werror -o build/cs50.o src/cs50.c
	gcc -o build/usr/lib/libcs50.so -shared build/cs50.o
	rm -f build/cs50.o
	cp src/cs50.h build/usr/include
	cp src/cs50.c build/usr/src
	find build -type d -exec chmod 0755 {} +
	find build -type f -exec chmod 0644 {} +

.PHONY: clean
clean:
	rm -rf build

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
	--provides $(NAME) \
	--conflicts "$(NAME) (<< $(VERSION))" \
	--replaces "$(NAME) (<= $(VERSION))" \
	--deb-no-default-config-files \
	--depends c-compiler \
	--description "$(DESCRIPTION)" \
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

# TODO: improve test suite
.PHONY: test
test: build hackerrank
	clang -ggdb3 -Ibuild/usr/include -O0 -std=c99 -Wall -Werror -Wno-deprecated-declarations tests/eprintf.c -Lbuild/usr/lib -lcs50 -o build/eprintf
	LD_LIBRARY_PATH=build/usr/lib build/eprintf
	clang -Ibuild -std=c11 -Wall -Werror -Wno-deprecated-declarations tests/hackerrank.c -o build/hackerrank
	build/hackerrank
