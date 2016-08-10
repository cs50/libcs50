#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "test_driver.h"

int main(void)
{
    struct dirent *dent;
    DIR *srcdir = opendir(".");
    Assertf(srcdir, "Opening current directory failed: %s", strerror(errno));

    while ((dent = readdir(srcdir)) != NULL)
    {
        struct stat st;
        if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0) continue;
        fstatat(dirfd(srcdir), dent->d_name, &st, 0); 
        if (!S_ISDIR(st.st_mode)) continue;

        printf("Beginning test \"%s\"\n", dent->d_name);
        char *exe = NULL;
        Assertf(asprintf(&exe, "%s/%s", dent->d_name, dent->d_name) != -1, "Memory allocation failure");

        char *infile = NULL;
        Assertf(asprintf(&infile, "%s.txt", exe) != -1, "Memory allocation failure");

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
            Assertf(status == 0, "Test \"%s\" failed", dent->d_name);
            printf("Test \"%s\" finished successfully\n", dent->d_name);
            free(infile);
            free(exe);
            close(fd);
        }
    }
    closedir(srcdir);


}

