#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef char *string;

/**
 * TODO
 */
string *read_file(const string pathname)
{
    // Open file
    FILE *file = fopen(pathname, "r");
    if (file == NULL)
    {
        return NULL;
    }

    // Allocate space for NULL-terminated array of lines
    string *lines = malloc(sizeof(string *));
    if (lines == NULL)
    {
        return NULL;
    }
    lines[0] = NULL;
    size_t size = 1;

    // Read chars
    long start = 0, end = 0;
    while (true)
    {
        // Read char
        int c = fgetc(file);

        // Check for line ending
        if (c == EOF || c == '\r' || c == '\n')
        {
            // If we've read a line with at least one char
            if (start != end)
            {
                // Allocate space for line
                string line = malloc(end - start + 1);
                if (line == NULL)
                {
                    // TODO
                    return NULL;
                }

                // Read string
                if (fseek(file, start, SEEK_SET) == -1 || fread(line, end - start, 1, file) != 1)
                {
                    // TODO
                    return NULL;
                }

                // Terminate string
                line[end - start] = '\0';

                // Extend array
                if (size == SIZE_MAX)
                {
                    // TODO
                    return NULL;
                }
                string *temp = realloc(lines, ++size);
                if (temp == NULL)
                {
                    // TODO
                    return NULL;
                }
                temp[size - 2] = line;
                temp[size - 1] = NULL;
                lines = temp;

                // Start of next line, if any
                start = end = end + 1;

                // Check for CR
                if (c == '\r')
                {
                    // Check for LF
                    int d = fgetc(file);
                    if (d == '\n')
                    {
                        // Ignore LF
                        start = end = end + 1;
                    }
                    else if (d != EOF)
                    {
                        // Unget char
                        if (ungetc(d, file) == EOF)
                        {
                            // TODO
                        }
                    }
                }
            }

            // End of file
            if (c == EOF)
            {
                break;
            }
        }

        // Not at end of file or line
        else
        {
            end++;
        }
    }

    // Return array of lines
    return lines;
}

int main(void)
{
    string *lines = read_file("read_file.txt");
    if (lines == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    for (int i = 0; lines[i] != NULL; i++)
    {
        printf("%s\n", lines[i]);
    }
}
