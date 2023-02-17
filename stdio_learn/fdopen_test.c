#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = -1;
    FILE *file = NULL;
    fd = open("BUILD.gn", O_RDONLY);
    if (fd < 0)
    {
        perror(strerror(errno));
        exit(1);
    }
    file = fdopen(fd, "rb");
    fclose(file);
    close(fd);
    printf("%d\n", fd);
    exit(0);
}
