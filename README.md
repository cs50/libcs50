# CS50 Library for C

## Development

Requires [Docker Toolbox](https://www.docker.com/products/docker-toolbox).

    docker-compose run cli # runs CS50 CLI
    make # builds all
    make lib # builds lib/libcs50.a
    make test # builds build/test

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

*   Change format of multi-line comments?
*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
