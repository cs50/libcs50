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

#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs50.h"

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
#undef eprintf
void eprintf(const char *file, int line, const char *format, ...)
{
    // print caller's file name and line number
    fprintf(stderr, "%s:%i: ", file, line);

    // variable argument list
    va_list ap;

    // last parameter before variable argument list is format
    va_start(ap, format);

    // print error message, formatted like printf
    vfprintf(stderr, format, ap);

    // invalidate variable argument list
    va_end(ap);
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent char; if text is not a single char, user is prompted
 * to retry. If line can't be read, returns CHAR_MAX.
 */
char get_char(string prompt)
{
    // try to get a char from user
    while (true)
    {
        // get line of text, returning CHAR_MAX on failure
        string line = get_string(prompt);
        if (line == NULL)
        {
            return CHAR_MAX;
        }

        // return a char if only a char was provided
        char c, d;
        if (sscanf(line, "%c%c", &c, &d) == 1)
        {
            return c;
        }

        // temporarily here for backwards compatibility
        if (prompt == NULL)
        {
            printf("Retry: ");
        }
    }
}
char GetChar(void)
{
    return get_char(NULL);
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent double as precisely as possible; if text does not represent
 * a double or if value would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns DBL_MAX.
 */
double get_double(string prompt)
{
    // try to get a double from user
    while (true)
    {
        // get line of text, returning DBL_MAX on failure
        string line = get_string(prompt);
        if (line == NULL)
        {
            return DBL_MAX;
        }

        // return a double if only a double was provided
        if (strlen(line) > 0 && !isspace((unsigned char) line[0]))
        {
            char *tail;
            errno = 0;
            double d = strtod(line, &tail);
            if (errno == 0 && *tail == '\0' && isfinite(d) != 0 && d < DBL_MAX)
            {
                // disallow hexadecimal and exponents
                if (strcspn(line, "XxEePp") == strlen(line))
                {
                    return d;
                }
            }
        }

        // temporarily here for backwards compatibility
        if (prompt == NULL)
        {
            printf("Retry: ");
        }
    }
}
double GetDouble(void)
{
    return get_double(NULL);
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent float as precisely as possible; if text does not represent
 * a float or if value would cause underflow or overflow, user is prompted
 * to retry. If line can't be read, returns FLT_MAX.
 */
float get_float(string prompt)
{
    // try to get a float from user
    while (true)
    {
        // get line of text, returning FLT_MAX on failure
        string line = get_string(prompt);
        if (line == NULL)
        {
            return FLT_MAX;
        }

        // return a float if only a float was provided
        if (strlen(line) > 0 && !isspace((unsigned char) line[0]))
        {
            char *tail;
            errno = 0;
            float f = strtof(line, &tail);
            if (errno == 0 && *tail == '\0' && isfinite(f) != 0 && f < FLT_MAX)
            {
                // disallow hexadecimal and exponents
                if (strcspn(line, "XxEePp") == strlen(line))
                {
                    return f;
                }
            }
        }

        // temporarily here for backwards compatibility
        if (prompt == NULL)
        {
            printf("Retry: ");
        }
    }
}
float GetFloat(void)
{
    return get_float(NULL);
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent int; if text does not represent an int in [-2^31, 2^31 - 1)
 * or would cause underflow or overflow, user is prompted to retry. If line
 * can't be read, returns INT_MAX.
 */
int get_int(string prompt)
{
    // try to get an int from user
    while (true)
    {
        // get line of text, returning INT_MAX on failure
        string line = get_string(prompt);
        if (line == NULL)
        {
            return INT_MAX;
        }

        // return an int if only an int (in range) was provided
        if (strlen(line) > 0 && !isspace((unsigned char) line[0]))
        {
            char *tail;
            errno = 0;
            long n = strtol(line, &tail, 10);
            if (errno == 0 && *tail == '\0' && n >= INT_MIN && n < INT_MAX)
            {
                return n;
            }
        }

        // temporarily here for backwards compatibility
        if (prompt == NULL)
        {
            printf("Retry: ");
        }
    }
}
int GetInt(void)
{
    return get_int(NULL);
}

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long long; if text does not represent a long long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LLONG_MAX.
 */
long long get_long_long(string prompt)
{
    // try to get a long long from user
    while (true)
    {
        // get line of text, returning LLONG_MAX on failure
        string line = get_string(prompt);
        if (line == NULL)
        {
            return LLONG_MAX;
        }

        // return a long long if only a long long (in range) was provided
        if (strlen(line) > 0 && !isspace((unsigned char) line[0]))
        {
            char *tail;
            errno = 0;
            long long n = strtoll(line, &tail, 10);
            if (errno == 0 && *tail == '\0' && n < LLONG_MAX)
            {
                return n;
            }
        }

        // temporarily here for backwards compatibility
        if (prompt == NULL)
        {
            printf("Retry: ");
        }
    }
}
long long GetLongLong(void)
{
    return get_long_long(NULL);
}

/**
 * Number of strings allocated by get_string.
 */
static size_t allocations = 0;

/**
 * Array of strings allocated by get_string.
 */
static string *strings = NULL;

/**
 * Prompts user for a line of text from standard input and returns
 * it as a string (char *), sans trailing line ending. Supports
 * CR (\r), LF (\n), and CRLF (\r\n) as line endings. If user
 * inputs only a line ending, returns "", not NULL. Returns NULL
 * upon error or no input whatsoever (i.e., just EOF). Stores string
 * on heap, but library's destructor frees memory on program's exit.
 */
string get_string(string prompt)
{
    // check whether we have room for another string
    if (allocations * sizeof(string) == SIZE_MAX)
    {
        return NULL;
    }

    // growable buffer for characters
    string buffer = NULL;

    // capacity of buffer
    size_t capacity = 0;

    // number of characters actually in buffer
    size_t size = 0;

    // character read or EOF
    int c;

    // prompt user
    if (prompt != NULL)
    {
        printf("%s", prompt);
    }

    // iteratively get characters from standard input, checking for CR (Mac OS), LF (Linux), and CRLF (Windows)
    while ((c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (size + 1 > capacity)
        {
            // initialize capacity to 16 (as reasonable for most inputs) and double thereafter
            if (capacity == 0)
            {
                capacity = 16;
            }
            else if (capacity <= (SIZE_MAX / 2))
            {
                capacity *= 2;
            }
            else if (capacity < SIZE_MAX)
            {
                capacity = SIZE_MAX;
            }
            else
            {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            string temp = realloc(buffer, capacity);
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[size++] = c;
    }

    // check whether user provided no input
    if (size == 0 && c == EOF)
    {
        return NULL;
    }
    
    // check whether user provided too much input (leaving no room for trailing NUL)
    if (size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    // if last character read was CR, try to read LF as well
    if (c == '\r' && (c = fgetc(stdin)) != '\n')
    {
        // return NULL if character can't be pushed back onto standard input
        if (c != EOF && ungetc(c, stdin) == EOF)
        {
            free(buffer);
            return NULL;
        }
    }

    // minimize buffer
    string s = realloc(buffer, size + 1);
    if (s == NULL)
    {
        free(buffer);
        return NULL;
    }

    // terminate string
    s[size] = '\0';

    // resize array so as to append string
    string *tmp = realloc(strings, sizeof(string) * (allocations + 1));
    if (tmp == NULL)
    {
        free(s);
        return NULL;
    }
    strings = tmp;

    // append string to array
    strings[allocations] = s;
    allocations++;

    // return string
    return s;
}
string GetString(void)
{
    // growable buffer for characters
    string buffer = NULL;

    // capacity of buffer
    size_t capacity = 0;

    // number of characters actually in buffer
    size_t size = 0;

    // character read or EOF
    int c;

    // iteratively get characters from standard input, checking for CR (Mac OS), LF (Linux), and CRLF (Windows)
    while ((c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (size + 1 > capacity)
        {
            // initialize capacity to 16 (as reasonable for most inputs) and double thereafter
            if (capacity == 0)
            {
                capacity = 16;
            }
            else if (capacity <= (SIZE_MAX / 2))
            {
                capacity *= 2;
            }
            else if (capacity < SIZE_MAX)
            {
                capacity = SIZE_MAX;
            }
            else
            {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            string temp = realloc(buffer, capacity);
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[size++] = c;
    }

    // check whether user provided no input
    if (size == 0 && c == EOF)
    {
        return NULL;
    }

    // check whether user provided too much input (leaving no room for trailing NUL)
    if (size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    // if last character read was CR, try to read LF as well
    if (c == '\r' && (c = fgetc(stdin)) != '\n')
    {
        // return NULL if character can't be pushed back onto standard input
        if (c != EOF && ungetc(c, stdin) == EOF)
        {
            free(buffer);
            return NULL;
        }
    }

    // minimize buffer
    string s = realloc(buffer, size + 1);
    if (s == NULL)
    {
        free(buffer);
        return NULL;
    }

    // terminate string
    s[size] = '\0';

    // return string
    return s;
}

/**
 * Called automatically before execution enters main.
 */
__attribute__((constructor))
static void setup(void)
{
    // disable buffering for standard output
    setvbuf(stdout, NULL, _IONBF, 0);
}

/**
 * Called automatically after execution exits main.
 */
__attribute__((destructor))
static void teardown(void)
{
    // free library's strings
    if (strings != NULL)
    {
        for (size_t i = 0; i < allocations; i++)
        {
            free(strings[i]);
        }
        free(strings);
    }
}
