#include <stddef.h>
#include <stdio.h>
#include <string.h>

int demo_strlen_test_main(int argc, char *argv[])
{
    char *str = "BlackHole\n";
    size_t length = strlen(str);
    printf("%s length %ld\n", str, length);
    return 0;
}
