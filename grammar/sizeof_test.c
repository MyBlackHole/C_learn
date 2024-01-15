#include <stdio.h>
#include <stdlib.h>

#define NUM 1000

int demo_sizeof_main(int argc, char *argv[])
{
    int *test = malloc(NUM);
    // 无法获取 malloc 空间大小
    printf("*p2-%ld\n", sizeof(*test));
    printf("p2-%ld\n", sizeof(test));
    exit(0);
}
