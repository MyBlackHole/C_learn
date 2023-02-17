#include <stdio.h>

/* 返回前面引导位0 的个数，如果a=0 的话， 不确定*/
int clz(unsigned int a) { return __builtin_clz(a); }

int main()
{
    unsigned int a = 0;
    a = 0;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 1;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 2;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 4;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 8;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 16;
    printf("0x%x ret=%d\n", a, clz(a));
    ;

    a = 0x0FFFFFFF;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 0x1FFFFFFF;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 0x2FFFFFFF;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 0x4FFFFFFF;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 0x8FFFFFFF;
    printf("0x%x ret=%d\n", a, clz(a));

    a = 0xFFFFFFFF;
    printf("0x%x ret=%d\n", a, clz(a));

    return 0;
}
