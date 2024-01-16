#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_access_main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "\tusage:%s <pathname>", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (access(argv[1], R_OK) < 0)
    {
        // 小于 0 代表不存在
        fprintf(stderr, "\taccess error for %s", argv[1]);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf(" \tread access OK\n");
    }

    if (open(argv[1], O_RDONLY) < 0)
    {
        fprintf(stderr, "\topen error for %s", argv[1]);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\topen for reading OK \n");
    }
    exit(EXIT_SUCCESS);
}
