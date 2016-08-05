DESCRIPTION = CS50 Library for C
MAINTAINER = CS50
NAME = library50-c
VERSION = 7.0.0

.PHONY: bash
bash:
	docker run -i --rm -v "$(PWD)":/root -t cs50/fpm
	#ID=$(docker build -q .) docker run -i -t $(ID)

.PHONY: build
build: clean Makefile src/cs50.c src/cs50.h
	mkdir -p build/usr/local/include
	mkdir -p build/usr/local/lib
	gcc -c -std=c99 -Wall -Werror -o build/cs50.o src/cs50.c
	ar rcs build/usr/local/lib/libcs50.a build/cs50.o
	rm -f build/cs50.o
	cp src/cs50.h build/usr/local/include
	chmod -R a+rX build

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
	--deb-no-default-config-files \
	--deb-use-file-permissions \
	--depends libc-dev \
	--description "$(DESCRIPTION)" \
	usr

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
	--pacman-use-file-permissions \
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
	--rpm-use-file-permissions \
	--description "$(DESCRIPTION)" \
	usr

# TODO: improve test suite
.PHONY: test
test: build
	gcc -ggdb3 -Ibuild/usr/local/include -O0 -std=c99 -Wall -Werror -Wno-deprecated-declarations tests/test.c -Lbuild/usr/local/lib -lcs50 -o build/test
