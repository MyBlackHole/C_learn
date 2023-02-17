#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    fp = fopen("/tmp/stdio_tmp", "r");
    if (fp == NULL)
    {
        // fprintf(stderr, "fopen() failed!  errno = %d\n", errno);
        perror("fopen()");
        // fprintf(stderr, "fopen() failed!  errno = %s\n", strerror(errno));
        exit(1);
    }

    puts("OK");

    fclose(fp);
    exit(0);
}
