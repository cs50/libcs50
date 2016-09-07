# CS50 Library for C

## Development

Requires [Docker Engine](https://docs.docker.com/engine/installation/).

    make bash
    make build # builds dynamic library
    make deb # builds .deb
    make pacman # builds .pkg.tar.xz
    make rpm # builds .rpm
    make test # builds test program

# Installation

1. Download the latest release per https://github.com/cs50/lib50-c/releases
1. Extract `lib50-c-*.*`
1. `cd lib50-c-*`
1. `make install`

## Usage

Link with `-lcs50`.

    #include <cs50.h>

    ...

    char c = get_char();
    double d = get_double();
    float f = get_float();
    int i = get_int();
    long long ll = get_long_long();
    string s = get_string();

## TODO

*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
