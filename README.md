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
2. Extract `libcs50-*.*`
3. `cd libcs50-*`
4. `sudo make install`

By default, we install to `/usr/local`. If you'd like to change the installation location, run
`sudo DESTDIR=/path/to/install make install` as desired.

### From Source (Windows / CMake) [using clang-MSVC-toolchain]
1. Download Visual Studio Build Tools
    - https://github.com/bycloudai/InstallVSBuildToolsWindows
        - Remember to enable C++ Clang Tools inside _**"Desktop Development with C++"**_

2. USAGE:-
    - [TERMINAL] 
        - `git clone <This Repository URL>`
    - [CMAKE]
        - `add_subdirectory("path/to/libcs50")`
        - `target_link_libraries(YOUR_APP_NAME PUBLIC cs50)`
    - [VSCode]
        - C/C++ Extensions Pack with CMAKE Tools [`ms-vscode.cmake-tools`]
        - `CMake: Select a Kit:- Clang`
        - for other IDEs, search up "how to use MSVC Clang Toolchain on windows"

3. CMake Introduction:-
    - https://www.youtube.com/playlist?list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s
        - watch first 6/7 videos, these are pretty short
    - CMake is just way too powerfull 😉

## Troubleshooting
1. If, when compiling a program, you see `/usr/bin/ld: cannot find -lcs50`:
Add `export LIBRARY_PATH=/usr/local/lib` to your `.bashrc`.
2. If, when compiling a program, you see `fatal error: 'cs50.h' file not found`:
Add `export C_INCLUDE_PATH=/usr/local/include` to your `.bashrc`.
3. If, when executing a program, you see `error while loading shared libraries: libcs50.so.8: cannot open shared object file: No such file or directory`:
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

See `man get_*` after installation, or [CS50 Reference](https://reference.cs50.net/cs50/)!

## TODO

*   Add tests.

## Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
