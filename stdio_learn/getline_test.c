#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    char *linebuf = NULL;
    size_t linesize = 0;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    while (1)
    {
        // 会连同换行一起读入
        if (getline(&linebuf, &linesize, fp) < 0)
        {
            break;
        }
        fprintf(stdout, "%lu\n", strlen(linebuf));
        fprintf(stdout, "%lu\n", linesize);
    }
    free(linebuf);

    fclose(fp);

    exit(0);
}
