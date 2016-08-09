#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "test_driver.h"
#include "cs50.h"

char const * const tests[] = {"get_char"};

int main(void)
{
    for (size_t i = 0; i < sizeof tests / sizeof *tests; i++)
    {
        char *exe = NULL;
        Assertf(asprintf(&exe, "%s/%s", tests[i], tests[i]) != -1, "%s", "Memory allocation failure");

        char *infile = NULL;
        Assertf(asprintf(&infile, "%s.txt", exe) != -1, "%s", "Memory allocation failure");

        int fd = open(infile, O_RDONLY);
        Assertf(fd != -1, "Error opening test input: %s", strerror(errno));

        pid_t p = fork();
        Assertf(p >= 0, "Forking failure. fork() returned %d", p);

        if (p == 0) // Child
        {
            Assertf(dup2(fd, STDIN_FILENO) != -1, "%s", "Could not replace stdin");
            Assertf(execl(exe, exe, (char *) NULL) != -1, "Execution failure: %s", strerror(errno));
        }
        else // Parent
        {
            int status = 0;
            waitpid(p, &status, 0);
            Assertf(status == 0, "Test \"%s\" failed", tests[i]);
            printf("Test \"%s\" finished successfully\n", tests[i]);
            free(infile);
            free(exe);
            close(fd);
        }
    }


}

