/****************************************************************************
 * CS50 Library 6
 * https://manual.cs50.net/library/
 *
 * Based on Eric Roberts' genlib.c and simpio.c.
 *
 * Copyright (c) 2013,
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
 *
 *
 * Contributors:
 *   Chad Sharp <crossroads1112@riseup.net>
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // Provides errno and ERANGE macro
#include "cs50.h"

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t) -1)
#endif



// Default capacity of buffer for standard input.
#define CAPACITY 128
// Base for strtol() and strtoll()
#define BASE 10
// Macro to reset errno if it has been changed
#define RESETERR(VAL) if (errno != VAL) errno = VAL
// Macro to cleanup upon function termination
#define CLEANUP(BUF, RET) free(BUF); return RET
// Macro used when the Get*() (except GetString()) recieve invalid input
#define RETRY(BUF) free(BUF); printf("Retry: ")



/*
 * Reads a line of text from standard input and returns the equivalent char; if
 * text does not represent a char, user is prompted to retry.  Leading and
 * trailing whitespace is ignored.  If line can't be read, returns CHAR_MAX.
 */

char
GetChar(void)
{
    // try to get a char from user
    while (true)
    {
        // get line of text, returning CHAR_MAX on failure
        string line = GetString();
        if (line == NULL)
        {
            return CHAR_MAX;
        }

        // return a char if only a char (possibly with
        // leading and/or trailing whitespace) was provided
        char c1, c2;
        if (sscanf(line, " %c %c", &c1, &c2) == 1)
        {
            CLEANUP(line, c1);
        }
        else
        {
            RETRY(line);
        }
    }
}


/*
 * Reads a line of text from standard input and returns the equivalent double
 * as precisely as possible; if text does not represent a double, user is
 * prompted to retry.  Leading and trailing whitespace is ignored.
 * Overflow/underflow detected.  If line can't be read, returns DBL_MAX.
 */

double
GetDouble(void)
{
    // try to get a double from user
    while (true)
    {
        // get line of text, returning DBL_MAX on failure
        string line = GetString();
        if (line == NULL)
        {
            return DBL_MAX;
        }

        // return a double if only a double (possibly with
        // leading and/or trailing whitespace) was provided
        char *endptr;
        int errnocpy = errno;
        double d = strtod(line, &endptr);
        if (errno != ERANGE && *endptr == '\0')
        {
            CLEANUP(line, d);
        }
        else
        {
            RESETERR(errnocpy);
            RETRY(line);
        }
    }
}


/*
 * Reads a line of text from standard input and returns the equivalent float as
 * precisely as possible; if text does not represent a float, user is prompted
 * to retry.  Leading and trailing whitespace is ignored.  If line can't be
 * read, returns FLT_MAX. Checks for overflow.
 */

float
GetFloat(void)
{
    // try to get a float from user
    while (true)
    {
        // get line of text, returning FLT_MAX on failure
        string line = GetString();
        if (line == NULL)
        {
            return FLT_MAX;
        }

        // return a float if only a float (possibly with
        // leading and/or trailing whitespace) was provided
        char *endptr;
        int errnocpy = errno;
        float f = strtof(line, &endptr);
        if (errno != ERANGE && *endptr == '\0')
        {
            CLEANUP(line, f);
        }
        else
        {
            RESETERR(errnocpy);
            RETRY(line);
        }
    }
}


/*
 * Reads a line of text from standard input and returns it as an int in the
 * range of [-2^31 + 1, 2^31 - 2] (on some systems), if possible; if text does
 * not represent such an int, user is prompted to retry.  Leading and trailing
 * whitespace is ignored. Overflow is detected and user is prompted to retry.
 * If line can't be read, returns INT_MAX.
 */

int
GetInt(void)
{
    // try to get an int from user
    while (true)
    {
        // get line of text, returning INT_MAX on failure
        string line = GetString();
        if (line == NULL)
        {
            return INT_MAX;
        }

        // return an int if only an int (possibly with
        // leading and/or trailing whitespace) was provided
        char *endptr;
        int errnocpy = errno;
        /* There is no strtoi() so we must check if n is
         * between INT_MAX and INT_MIN. On most systems
         * a long is the same size as an int but not on all. */
        long n = strtol(line, &endptr, BASE);
        if (errno != ERANGE && *endptr == '\0' && n <= INT_MAX && n >= INT_MIN)
        {
            CLEANUP(line, (int) n);
        }
        else
        {
            RESETERR(errnocpy);
            RETRY(line);
        }
    }
}


/*
 * Reads a line of text from standard input and returns an equivalent long long
 * in the range [-2^63 + 1, 2^63 - 2] (on some sysytems), if possible; if text
 * does not represent such a long long, user is prompted to retry.  Leading and
 * trailing whitespace is ignored. Overflow is detected and user prompted to
 * retry. If line can't be read, returns LLONG_MAX.
 */

long long
GetLongLong(void)
{
    // try to get a long long from user
    while (true)
    {
        // get line of text, returning LLONG_MAX on failure
        string line = GetString();
        if (line == NULL)
        {
            return LLONG_MAX;
        }

        // return a long long and only a long long, checking for
        // overflow. Will skip over whitespace.
        char *endptr;
        int errnocpy = errno;
        long long n = strtoll(line, &endptr, BASE);
        if (errno != ERANGE && *endptr == '\0')
        {
            CLEANUP(line, n);
        }
        else
        {
            RESETERR(errnocpy);
            RETRY(line);
        }
    }
}


/*
 * Reads a line of text from standard input and returns it as a string, sans
 * trailing newline character.  (Ergo, if user inputs only "\n", returns "" not
 * NULL.)  Leading and trailing whitespace is not ignored.  Returns NULL upon
 * error or no input whatsoever (i.e., just EOF).
 */


string
GetString(void)
{
    // growable buffer for chars
    string buffer = NULL;

    // capacity of buffer
    size_t capacity = 0;

    // number of chars actually in buffer
    size_t n = 0;

    // character read or EOF
    int c;

    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (n + 1 >= capacity)
        {
            // determine new capacity: start at CAPACITY then double
            if (capacity == 0)
            {
                capacity = CAPACITY;
            }
            else if (capacity <= (SIZE_MAX / 2))
            {
                capacity *= 2;
            }
            else if (capacity < (SIZE_MAX - 1))
            {
                capacity += ((SIZE_MAX - capacity)/2);
            }
            else
            {
                CLEANUP(buffer, NULL);
            }

            // extend buffer's capacity
            // Better practice to use sizeof(*temp) than sizeof(char);
            // http://stackoverflow.com/questions/7243872/why-write-sizeofchar-if-char-is-1-by-standard
            string temp = realloc(buffer, capacity * sizeof(*temp));
            if (temp == NULL)
            {
                CLEANUP(buffer, NULL);
            }

            buffer = temp;
        }

        // append current character to buffer
        buffer[n++] = c;
    }

    // return NULL if user provided no input
    if (n == 0 && c == EOF)
    {
        return NULL;
    }


    string minimal = realloc(buffer, (n + 1) * sizeof(*minimal));
    // Check if realloc failed
    if (minimal == NULL)
    {
        // Minimization failed. Input should still be returned
        minimal = buffer;
    }

    // terminate string
    minimal[n] = '\0';

    // return string
    return minimal;
}
