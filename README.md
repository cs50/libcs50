# CS50 Library for C

[![Build Status](https://travis-ci.org/cs50/libcs50.svg?branch=master)](https://travis-ci.org/cs50/libcs50)

## Development

`make`: builds dynamic library

`make deb`: builds source deb

`make install`: installs the library under `/usr/local` by default (set `DESTDIR` to change that)

## Installation

### Ubuntu

```
$ curl -s https://packagecloud.io/install/repositories/cs50/repo/script.deb.sh | sudo bash
$ sudo apt-get install libcs50
```

### Fedora

```
$ curl -s https://packagecloud.io/install/repositories/cs50/repo/script.rpm.sh | sudo bash
$ yum install libcs50
```

### From Source (Linux and Mac)

1. Download the latest release from https://github.com/cs50/libcs50/releases
1. Extract `libcs50-*.*`
1. `cd libcs50-*`
1. `sudo make install`

By default, we install to `/usr/local`. If you'd like to change the installation location, run
`sudo DESTDIR=/path/to/install make install` as desired.

## Troubleshooting
1. If, when compiling a program, you see `/usr/bin/ld: cannot find -lcs50`:
Add `export LIBRARY_PATH=/usr/local/lib` to your `.bashrc`.
1. If, when compiling a program, you see `fatal error: 'cs50.h' file not found`:
Add `export C_INCLUDE_PATH=/usr/local/include` to your `.bashrc`.
1. If, when executing a program, you see `error while loading shared libraries: libcs50.so.8: cannot open shared object file: No such file or directory`:
Add `export LD_LIBRARY_PATH=/usr/local/lib` to your `.bashrc`.

Close and reopen any terminal windows.

## Usage

Link with `-lcs50`.

    #include <cs50.h>

    ...
    char c = get_char("Prompt: ");
    double d = get_double("Prompt: ");
    float f = get_float("Prompt: ");
    int i = get_int("Prompt: ");
    long l = get_long("Prompt: ");
    string s = get_string("Prompt: ");

    // deprecated as of fall 2017
    long long ll = get_long_long("Prompt: ");

## Documentation

See `man get_*` and `man eprintf` after installation, or [CS50 Reference](https://reference.cs50.net/cs50/)!

## TODO

*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
