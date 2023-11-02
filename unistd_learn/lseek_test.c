#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd_i = 0;
    if (argc < 2)
    {
        fprintf(stderr, "<path>\n");
        exit(1);
    }

    fd_i = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    lseek(fd_i, 5LL * 1024LL * 1024LL * 1024LL - 1LL, SEEK_SET);

    write(fd_i, "", 1);

    close(fd_i);

    exit(0);
}
