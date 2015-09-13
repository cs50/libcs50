/****************************************************************************
 * CS50 Library 4
 * https://manual.cs50.net/Library
 *
 * Based on Eric Roberts' genlib.c and simpio.c.
 *
 * Copyright (c) 2011,
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
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cs50.h"


/*
 * Reads a line of text from standard input and returns the equivalent
 * char; if text does not represent a char, user is prompted to retry.
 * Leading and trailing whitespace is ignored.  If line can't be read,
 * returns CHAR_MAX.
 */

char GetChar(void)
{
    // Declaration always at top.
    // Performance issues
    string line;
    char data;
    char badc;
    
    // try to get a char from user
    while (true)
    {
        // get line of text, returning CHAR_MAX on failure
        line = GetString();
        
        if (!line)
            return CHAR_MAX;

        // return a char if only a char (possibly with
        // leading and/or trailing whitespace) was provided
        if (sscanf(line, " %c %c", &data, &badc) == 1)
        {
            free(line);
            return data;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}


/*
 * Reads a line of text from standard input and returns the equivalent
 * double as precisely as possible; if text does not represent a
 * double, user is prompted to retry.  Leading and trailing whitespace
 * is ignored.  For simplicity, overflow and underflow are not detected.
 * If line can't be read, returns DBL_MAX.
 */

double GetDouble(void)
{
    string line;
    double data;
    char badc;
    // try to get a double from user
    while (true)
    {
        // get line of text, returning DBL_MAX on failure
        line = GetString();
        
        if (!line)
            return DBL_MAX;

        // return a double if only a double (possibly with
        // leading and/or trailing whitespace) was provided
        if (sscanf(line, " %lf %c", &data, &badc) == 1)
        {
            free(line);
            return data;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}


/*
 * Reads a line of text from standard input and returns the equivalent
 * float as precisely as possible; if text does not represent a float,
 * user is prompted to retry.  Leading and trailing whitespace is ignored.
 * For simplicity, overflow and underflow are not detected.  If line can't
 * be read, returns FLT_MAX.
 */

float GetFloat(void)
{
    string line;
    float data;
    char badc;
    
    // try to get a float from user
    while (true)
    {
        // get line of text, returning FLT_MAX on failure
        line = GetString();
        
        if (!line)
            return FLT_MAX;

        // return a float if only a float (possibly with
        // leading and/or trailing whitespace) was provided
        if (sscanf(line, " %f %c", &data, &badc) == 1)
        {
            free(line);
            return f;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}


/*
 * Reads a line of text from standard input and returns it as an
 * int in the range of [-2^31 + 1, 2^31 - 2], if possible; if text
 * does not represent such an int, user is prompted to retry.  Leading
 * and trailing whitespace is ignored.  For simplicity, overflow is not
 * detected.  If line can't be read, returns INT_MAX.
 */

int GetInt(void)
{
    string line;
    int data;
    char badc;
    
    // try to get an int from user
    while (true)
    {
        // get line of text, returning INT_MAX on failure
        line = GetString();
        
        if (!line)
            return INT_MAX;

        // return an int if only an int (possibly with
        // leading and/or trailing whitespace) was provided
        if (sscanf(line, " %d %c", &data, &badc) == 1)
        {
            free(line);
            return n;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}


/*
 * Reads a line of text from standard input and returns an equivalent
 * long long in the range [-2^63 + 1, 2^63 - 2], if possible; if text
 * does not represent such a long long, user is prompted to retry.
 * Leading and trailing whitespace is ignored.  For simplicity, overflow
 * is not detected.  If line can't be read, returns LLONG_MAX.
 */

long long GetLongLong(void)
{
    string line;
    long long data;
    char badc;
    
    // try to get a long long from user
    while (true)
    {
        // get line of text, returning LLONG_MAX on failure
        line = GetString();
        
        if (!line)
            return LLONG_MAX;

        // return a long long if only a long long (possibly with
        // leading and/or trailing whitespace) was provided
        if (sscanf(line, " %lld %c", &data, &badc) == 1)
        {
            free(line);
            return n;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}


/*
 * Reads a line of text from standard input and returns it as a
 * string (char*), sans trailing newline character.  (Ergo, if
 * user inputs only "\n", returns "" not NULL.)  Returns NULL
 * upon error or no input whatsoever (i.e., just EOF).  Leading
 * and trailing whitespace is not ignored.  Stores string on heap
 * (via malloc); memory must be freed by caller to avoid leak.
 */

string GetString(void)
{
    // growable buffer for chars
    string buffer = NULL;

    // capacity of buffer
    unsigned int capacity = 0;

    // number of chars actually in buffer
    unsigned int size = 0;

    // character read or EOF
    int c;
    
    // temp string
    string temp = NULL;
    
    // final string
    string minimal = NULL;

    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (size + 1 > capacity)
        {
            // determine new capacity: start at 32 then double
            if (capacity == 0)
                capacity = 32;
            else if (capacity <= (UINT_MAX / 2))
                capacity *= 2;
            else
            {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            temp = realloc(buffer, capacity * sizeof(char));
            
            if (!temp)
            {
                free(buffer);
                return NULL;
            }
            
            buffer = temp;
        }

        // append current character to buffer
        buffer[size++] = c;
    }

    // return NULL if user provided no input
    if (size == 0 && c == EOF)
        return NULL;

    // minimize buffer
    minimal = malloc((size + 1) * sizeof(char));
    strncpy(minimal, buffer, size);
    free(buffer);

    // terminate string
    minimal[size] = '\0';

    // return string
    return minimal;
}
