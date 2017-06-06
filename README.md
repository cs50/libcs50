# CS50 Library for C

[![Build Status](https://travis-ci.org/cs50/libcs50.svg?branch=master)](https://travis-ci.org/cs50/libcs50)

## Development

`make build`: builds dynamic library
 
`make deb`: builds source deb
 
`make hack`: combines library into `cs50.h`
 
`make install`: installs the library under `/usr/local` by default (set `DESTDIR` to change that)

## Releasing

Requires [Docker Engine](https://docs.docker.com/engine/installation/).

Before merging into `master`, be sure to add an entry to `debian/changelog`:

1. Install `cli50` Python package:
    ```
    $ pip install cli50
    ```
1. Mount `libcs50` into a `cs50/cli` container:
    ```
    $ cd path/to/libcs50
    $ cli50
    ```
1. Run the following commands inside the `cs50/cli` container:
    ```
    $ dch -u low -v VERSION-0ubuntu1 # then list your changes, save, and exit
    $ dch -r trusty
    ```

    Be sure to replace `VERSION` with the actual version (e.g., `8.0.3`). If, for some reason, you're not using a `cs50/cli` container, be sure to set `DEBFULLNAME` and `DEBEMAIL` to `CS50 Sysadmins` and `sysadmins@cs50.harvard.edu` respectively:
    ```
    $ DEBFULLNAME="CS50 Sysadmins" DEBEMAIL="sysadmins@cs50.harvard.edu" dch -u low -v VERSION-0ubuntu1
    ```

## Installation

### Ubuntu

```
$ sudo apt-add-repository ppa:cs50/ppa
$ sudo apt-get update
$ sudo apt-get install libcs50
```

### From Source

1. Download the latest release per https://github.com/cs50/libcs50/releases
1. Extract `libcs50-*.*`
1. `cd libcs50-*`
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

## Documentation

See `man get_*` after installation, or [CS50 Reference](https://reference.cs50.net/cs50/)!

## TODO

*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
