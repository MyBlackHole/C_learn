#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unctrl.h>

// ❯ ./out/obj/string_learn/strrchr_test
// :8080
int main(int argc, char* argv[])
{
    char* str = "127.0.0.1:8080";
    char* str_1;
    str_1 = strrchr(str, ':');
    printf("%s\n", str_1);
    return EXIT_SUCCESS;
}
