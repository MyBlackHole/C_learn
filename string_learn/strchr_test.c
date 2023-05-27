#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *tmp_s;
    char *s = "black,hole";
    // 返回切去 ',' 前字符串
    tmp_s = strchr(s, ',');
    printf("%s\n", tmp_s);
    return EXIT_SUCCESS;
}
