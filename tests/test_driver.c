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

#define BUF_SIZE 4096

static void check_output(int fd, char *outfile);

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

        char *outfile = NULL;
        Assertf(asprintf(&outfile, "%s/output.txt", dent->d_name) != -1, "Memory allocation failure");

        char *infile = NULL;
        Assertf(asprintf(&infile, "%s/input.txt", dent->d_name) != -1, "Memory allocation failure");

        int in_fd = open(infile, O_RDONLY);
        Assertf(in_fd != -1, "Error opening test input: %s", strerror(errno));

        // Create pipe
        int p[2];
        pipe(p);

        pid_t pid = fork();
        Assertf(pid >= 0, "Forking failure. fork() returned %d", pid);

        if (pid == 0) // Child
        {
            // Child writes to pipe, reads from input.txt
            close(p[0]);

            // Child should enter test directory
            chdir(dent->d_name);
            Assertf(dup2(p[1], STDOUT_FILENO) != -1, "%s", "Could not replace stdout");
            Assertf(dup2(in_fd, STDIN_FILENO) != -1, "%s", "Could not replace stdin");
            Assertf(execl("test", "test", (char *) NULL) != -1, "Execution failure: %s/test: %s", dent->d_name, strerror(errno));
        }
        else // Parent
        {
            close(p[1]);
            int status = 0;
            waitpid(pid, &status, 0);
            Assertf(status == 0, "Test \"%s\" failed", dent->d_name);
            check_output(p[0], outfile);
            printf("Test \"%s\" finished successfully\n", dent->d_name);

            // Cleanup
            free(infile);
            free(outfile);
            close(in_fd);
        }
    }
    closedir(srcdir);


}

static void check_output(int fd, char *outfile)
{

    char child_buf[BUF_SIZE] = {0};
    int bytes = read(fd, child_buf, BUF_SIZE - 1);
    // Attempt to open outfile
    int out_fd = open(outfile, O_RDONLY);
    if (out_fd == -1)
    {
        char answer, dummy;
        do
        {
            printf("%s doesn't seem to exist." \
                   "Would you like to create it using the output on the following line?", outfile);
            printf("\n%s\n[y/n]: ", (bytes) ? child_buf : "(Child produced no output)");
            fflush(stdout);
        } while (scanf("%c%c", &answer, &dummy) == 1 && (answer == 'y' || answer == 'n'));

        if (answer == 'y')
        {
            out_fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
            Assertf(out_fd != -1, "Failed to open file for writing: %s", strerror(errno));
            Assertf(write(out_fd, child_buf, bytes) != -1, "Error writing to output file %s", strerror(errno));
            close(out_fd);
        }
    }
    else
    {
        char out_buf[BUF_SIZE] = {0};
        int out_bytes = read(out_fd, out_buf, BUF_SIZE - 1);
        Assertf(out_bytes != -1, "Error reading from outfile: %s", strerror(errno));
        close(out_fd);

        // Remove trailing newline from outfile
        if (out_buf[out_bytes-1] == '\n') out_buf[out_bytes-1] = '\0';
        Assertf(strcmp(out_buf, child_buf) == 0, "Outputs did not match. Expected \"%s\" found \"%s\"", out_buf, child_buf);
    }
}
