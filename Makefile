DESCRIPTION = CS50 Library for C
MAINTAINER = CS50 <sysadmins@cs50.harvard.edu>
NAME = library50-c
VERSION = 7.0.0

.PHONY: bash
bash:
	# docker-compose up # https://github.com/docker/compose/issues/3106
	docker build . -t library-c
	docker run -i --rm -t -v "$(PWD):/root" library-c

.PHONY: build
build: clean Makefile src/cs50.c src/cs50.h
	mkdir -p build/usr/local/include
	mkdir -p build/usr/local/lib
	gcc -c -fPIC -std=c99 -Wall -Werror -o build/cs50.o src/cs50.c
	gcc -o build/usr/local/lib/libcs50.so -shared build/cs50.o
	rm -f build/cs50.o
	cp src/cs50.h build/usr/local/include
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
	--deb-no-default-config-files \
	--depends c-compiler \
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
test: build
	gcc -ggdb3 -Ibuild/usr/local/include -O0 -std=c99 -Wall -Werror -Wno-deprecated-declarations tests/test.c -Lbuild/usr/local/lib -lcs50 -o build/test
