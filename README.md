# CS50 Library for C
![Build Status](https://codeship.com/projects/2f287c50-437e-0134-7ad2-76dd7bf7b13e/status?branch=master)

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
*   Move installation from `/usr/local` to `/usr` or `/opt`.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
