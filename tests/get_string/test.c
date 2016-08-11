#include <stdio.h>
#include <string.h>
#include "../test_driver.h"

#define MAX_LINE 4096

static void remove_newlines(char *line, int len);

int main(void)
{
    char line[MAX_LINE];
    // fgets will operate on different stream but same file as get_string
    FILE *in = fopen("./input.txt", "r"); 
    while (fgets(line, MAX_LINE, in))
    {
        size_t len = strlen(line);
        remove_newlines(line, (int) len);
        char *test = get_string();
        Assertf(strncmp(line, test, len) == 0, 
                "Expected \"%s\", got \"%s\"", line, test);
    }
    fclose(in);
}

static void remove_newlines(char *line, int len)
{
    for (int i = len - 2; i < len; i++)
    {
        if (i < 0) continue; // len could be 0 or 1
        if (line[i] == '\n' || line[i] == '\r')
        {
            line[i] = '\0';
            break;
        }
    }
}
