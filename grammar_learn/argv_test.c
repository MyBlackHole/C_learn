#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++)
    { /* echo all command-line args */
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    exit(0);
}
