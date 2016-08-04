# CS50 Library for C

## Development

Requires [Docker Engine](https://docs.docker.com/engine/installation/).

    make bash
    make build # builds static library
    make deb # builds .deb
    make pacman # builds .pkg.tar.xz
    make rpm # builds .rpm
    make test # builds test program

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
*   Test `eprintf`.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
