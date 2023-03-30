#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            perror("write error");
            exit(EXIT_FAILURE);
        }
    }

    if (n < 0)
    {
        perror("read error");
    }

    exit(EXIT_SUCCESS);
}
