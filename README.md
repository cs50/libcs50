# CS50 Library for C

[![Build Status](https://travis-ci.org/cs50/libcs50.svg?branch=master)](https://travis-ci.org/cs50/libcs50)

## Development

`make`: builds dynamic library

`make deb`: builds source deb

`make hack`: combines library into `cs50.h`

`make install`: installs the library under `/usr/local` by default (set `DESTDIR` to change that)

## Installation

### Ubuntu

```
$ sudo apt-add-repository ppa:cs50/ppa
$ sudo apt-get update
$ sudo apt-get install libcs50
```

### From Source (Linux and Mac)

1. Download the latest release per https://github.com/cs50/libcs50/releases
1. Extract `libcs50-*.*`
1. `cd libcs50-*`
1. `gem install asciidoctor`, as needed

If on Mac:
* `make install`

If on Linux:
* `sudo make install`

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

## Documentation

See `man get_*` and `man eprintf` after installation, or [CS50 Reference](https://reference.cs50.net/cs50/)!

## TODO

*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
