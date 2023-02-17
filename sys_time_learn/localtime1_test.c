#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME "/tmp/out"

#define BUFSIZE 1024

int main()
{
    FILE *fp = NULL;
    char buf[BUFSIZE];
    int count = 0;
    time_t stamp;
    struct tm *tm = NULL;

    fp = fopen(FNAME, "a+");
    if (fp == NULL)
    {
        perror("fopen erron");
        exit(1);
    }

    while (fgets(buf, BUFSIZE, fp) != NULL)
    {
        count++;
    }

    while (1)
    {
        time(&stamp);
        tm = localtime(&stamp);
        fprintf(fp, "%d----%d-%d-%d %d:%d:%d\n", ++count, tm->tm_year + 1900,
                tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min,
                tm->tm_sec);
        fflush(fp);
        sleep(1);
    }

    fclose(fp);

    exit(0);
}
