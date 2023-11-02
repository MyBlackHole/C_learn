#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = -1;
	fd = open("/root/test/2.txt", O_RDONLY | 0, 0);
    if (fd <= 0)
    {
        perror("open()");
        exit(1);
    }

    puts("OK");

    close(fd);
    exit(EXIT_SUCCESS);
}
