#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *s = "BlackHole\n";
    size_t length = strlen(s);
    printf("%s length %ld\n", s, length);
    return 0;
}
