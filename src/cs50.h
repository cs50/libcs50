/**
 * CS50 Library for C
 * https://github.com/cs50/libcs50
 *
 * Based on Eric Roberts' genlib.c and simpio.c.
 *
 * Copyright (c) 2017,
 * Glenn Holloway <holloway@eecs.harvard.edu>
 * David J. Malan <malan@harvard.edu>
 * All rights reserved.
 *
 * BSD 3-Clause License
 * http://www.opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of CS50 nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CS50_H
#define _CS50_H

#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Temporarily used to make arguments to get_* (but not Get*) optional.
 * Inspired by https://gustedt.wordpress.com/2010/06/03/default-arguments-for-c99/.
 */
#ifdef __GNUC__
#define _ARGS(_0, _1, _2, ...) _2
#define ARGS(...) _ARGS(, ##__VA_ARGS__, 1, 0)
#define ARG_0(NAME) NULL
#define ARG_1(NAME, a) a
#define __ZERO_OR_ONE_ARG(NAME, N, ...) ARG_ ## N (NAME, ##__VA_ARGS__)
#define _ZERO_OR_ONE_ARG(NAME, N, ...) __ZERO_OR_ONE_ARG(NAME, N, ##__VA_ARGS__)
#define ZERO_OR_ONE_ARG(NAME, ...) NAME(_ZERO_OR_ONE_ARG(NAME, ARGS(__VA_ARGS__), ##__VA_ARGS__))
#endif 

/**
 * Our own data type for string variables.
 */
typedef char *string;

/**
 * Prints an error message, formatted like printf, to standard error, prefixing it with
 * file name and line number from which function was called (which a macro provides).
 *
 * This function is not intended to be called directly. Instead, call the macro of the same name,
 * which expects fewer arguments.
 *
 * Inspired by http://www.gnu.org/software/libc/manual/html_node/Variable-Arguments-Output.html
 * http://www.gnu.org/software/libc/manual/html_node/Error-Messages.html#Error-Messages, and
 * https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html.
 */
void eprintf(const char *file, int line, const char *format, ...) __attribute__((format(printf, 3, 4)));

/**
 * Macro that allows function of the same name to be called without specifying caller's
 * file name or line number explicitly.
 */
#define eprintf(format, ...) eprintf(__FILE__, __LINE__, format, ##__VA_ARGS__)

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent char; if text is not a single char, user is prompted
 * to retry. If line can't be read, returns CHAR_MAX.
 */
char get_char(string prompt);
char GetChar(void) __attribute__((deprecated));
#ifdef __GNUC__
#define get_char(...) ZERO_OR_ONE_ARG(get_char, ##__VA_ARGS__)
#endif

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent double as precisely as possible; if text does not represent
 * a double or if value would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns DBL_MAX.
 */
double get_double(string prompt);
double GetDouble(void) __attribute__((deprecated));
#ifdef __GNUC__
#define get_double(...) ZERO_OR_ONE_ARG(get_double, ##__VA_ARGS__)
#endif

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent float as precisely as possible; if text does not represent
 * a float or if value would cause underflow or overflow, user is prompted
 * to retry. If line can't be read, returns FLT_MAX.
 */
float get_float(string prompt);
float GetFloat(void) __attribute__((deprecated));
#ifdef __GNUC__
#define get_float(...) ZERO_OR_ONE_ARG(get_float, ##__VA_ARGS__)
#endif

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent int; if text does not represent an int in [-2^31, 2^31 - 1)
 * or would cause underflow or overflow, user is prompted to retry. If line
 * can't be read, returns INT_MAX.
 */
int get_int(string prompt);
int GetInt(void) __attribute__((deprecated));
#ifdef __GNUC__
#define get_int(...) ZERO_OR_ONE_ARG(get_int, ##__VA_ARGS__)
#endif

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long long; if text does not represent a long long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LLONG_MAX.
 */
long long get_long_long(string prompt);
long long GetLongLong(void) __attribute__((deprecated));
#ifdef __GNUC__
#define get_long_long(...) ZERO_OR_ONE_ARG(get_long_long, ##__VA_ARGS__)
#endif

/**
 * Prompts user for a line of text from standard input and returns
 * it as a string (char *), sans trailing line ending. Supports
 * CR (\r), LF (\n), and CRLF (\r\n) as line endings. If user
 * inputs only a line ending, returns "", not NULL. Returns NULL
 * upon error or no input whatsoever (i.e., just EOF). Stores string
 * on heap, but library's destructor frees memory on program's exit.
 */
string get_string(string prompt);
string GetString(void) __attribute__((deprecated));
#ifdef __GNUC__
#define get_string(...) ZERO_OR_ONE_ARG(get_string, ##__VA_ARGS__)
#endif

#endif
