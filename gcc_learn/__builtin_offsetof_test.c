#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// #define offsetof(type, member) (int)(&((type *)0)->member)

// // 偏移量
// #define offsetof(type, member) __builtin_offsetof(type, member)

typedef struct _test
{
    char i;
    int j;
    char k;
} Test;
//
int main(int argc, char *argv[])
{
    Test *p = malloc(sizeof(Test));
    p->j = 100;
    printf("%ld -- %p -- %d\n", offsetof(Test, j), p,
           *(int *)((size_t)p + offsetof(Test, j)));
    return EXIT_SUCCESS;
}
