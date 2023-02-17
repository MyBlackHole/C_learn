#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 100
void error_handling(char *message);

int main(int argc, char *argv[])
{
    char *path = dirname(argv[0]);
    char *filename = "data.txt";
    char *name = malloc(strlen(path) + strlen(filename));

    strcpy(name, path);
    strcat(name, filename);

    int fd;
    char buf[BUF_SIZE];

    fd = open(name, O_RDONLY);
    if (fd == -1)
    {
        error_handling("open() error!");
    }
    printf("file descriptor: %d \n", fd);

    if (read(fd, buf, sizeof(buf)) == -1)
    {
        error_handling("read() error!");
    }
    printf("file data: %s", buf);
    close(fd);
    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
