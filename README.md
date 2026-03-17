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

To use the CS50 Library for C, you must include the header file at the top of your C file:

```c
#include <cs50.h>
```

When compiling, you must also link the library by adding the `-lcs50` flag:

```bash
gcc program.c -o program -lcs50
```

### Usage Example:
```
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
```


## Functions

The library provides several functions for getting input from the user via standard input (`stdin`). Each function displays a prompt to the user and ensures the input matches the expected data type, re-prompting the user if the input is invalid.

#### `get_char`
Prompts the user for a single `char`.
```c
char c = get_char("Enter a character: ");
```

#### `get_double`
Prompts the user for a `double` (floating-point number with double precision).
```c
double d = get_double("Enter a double: ");
```

#### `get_float`
Prompts the user for a `float` (floating-point number).
```c
float f = get_float("Enter a float: ");
```

#### `get_int`
Prompts the user for an `int` (integer).
```c
int i = get_int("Enter an integer: ");
```

#### `get_long`
Prompts the user for a `long` (a larger integer).
```c
long l = get_long("Enter a long: ");
```

#### `get_string`
Prompts the user for a sequence of characters (a "string"). In the CS50 library, `string` is a type alias for `char *`.
```c
string s = get_string("What's your name? ");
```

### Example

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name? ");
    int age = get_int("How old are you? ");
    
    printf("Hello, %s! You are %i years old.\n", name, age);
}
```

## Documentation

See `man get_*` after installation, or [CS50 Reference](https://reference.cs50.net/cs50/)!

## TODO

*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
