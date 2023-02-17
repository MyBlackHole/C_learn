#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buf[1000];

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    while (fgets(buf, 1000, f))
    {
        printf("%s\n", buf);
    }
    return 0;
}
