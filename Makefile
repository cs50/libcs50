all: lib test

build:
	rm -rf build
	mkdir build
	clang -c -std=c99 -Wall -Werror -fPIC -o build/cs50.o src/cs50.c

lib: build
	rm -rf lib
	mkdir lib
	clang -shared -o lib/libcs50.so build/cs50.o

test: lib
	clang -ggdb3 -Isrc -O0 -std=c99 -Wall -Werror -Wno-deprecated-declarations tests/test.c -Llib -lcs50 -o build/test

clean:
	rm -rf build/ lib/
