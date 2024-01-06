/*
 * 逻辑测试
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * 1
 * 逻辑 True ? 1: 2
 *
 * 2
 * |=
 *
 * 3
 * &=
 *
 * 4
 * ~
 *
 * 5
 * 十进制、八进制、十六进制
 *
 */
struct test1
{
    /* data */
    int a : 2;
    int b;
} tt;

int func9()
{
    struct test1 ttt;
    ttt.b = 9;
    printf("%p\n", &tt);
    printf("%p\n", &tt.b);
    unsigned long int count = (unsigned long int)&tt.b - (unsigned long int)&tt;
    printf("%lu\n", count);
    printf("%p\n", &ttt);
    printf("%p\n", &ttt.b);
    unsigned long int a = (unsigned long int)&ttt;
    printf("%lu\n", a);

    ttt.a = 1;

    // int
    printf("%d\n", *(int *)((unsigned long int)&ttt + count));
    printf("%d\n", ttt.a);
    return 0;
}

int func8()
{
    printf("%p\n", &tt);
    printf("%p\n", &tt);
    printf("%lu\n", sizeof(tt));
    return 0;
}

struct test
{
    /* data */
    int a : 2;
};

int func7()
{
    struct test t = {0};
    printf("%d\n", t.a);
    return 0;
}

int func6()
{
    int i = 1000;
    printf("八进制:%d\n", (i));
    return 0;
}

int func5()
{
    int i = 1000;
    printf("八进制:%o\n", i);
    printf("十进制:%d\n", i);
    printf("十六进制:%X\n", ~0);
    return 0;
}

int func4()
{
    int i = 0;
    printf("%d", ~i);
    return 0;
}

int func3()
{
    int i = 0;
    i &= 1 << 2;
    printf("%d", i);
    return 0;
}

int func2()
{
    int i = 0;
    i |= 1 << 2;
    printf("%d", i);
    return 0;
}

int func1()
{
    printf("%d\n", 1 ? 1 : 2);
    return 0;
}

void func10()
{
    if (1)
    {
        printf("%d\n", 0);
    }
    return;
}

void func11()
{
    int i = 1;
    printf("%d", 1 + --i);
}

void func12()
{
    int i = 1;
    printf("%d", 1 + --i), printf("ok");
}

void func13()
{
    int i = -1;
    printf("%d\n", i & 256);
}

/* # define EV_A */
/* void func13() { */
/*   if (!EV_A) { */
/*     printf("触发了"); */
/*   } */
/*   printf("退出了"); */
/* } */

void func14()
{
    char c;
    char *str = "abcd";
    c = *str++;
    printf("%c\n", c);
    printf("%c\n", *str);
}

void func15()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%ld\n", tv.tv_sec ^ tv.tv_usec ^ getpid());
}

void func16() { printf("%ld\n", sizeof(double)); }

void func17()
{
    int a;
    double x = 1.1, y = 3.2;
    a = x + y;
    printf("%d\n", a);
}

void func18()
{
    int test = 1, z = 1;
    printf("%d\n", (++test + z++));
}

void func19()
{
    char *s = "abckd";
    printf("%s\n", (s + 3));
}

int demo_2_main()
{
    func17();
    // const int a = 0;
    // char c = 'A';
    // printf("111%d\n", a++);
    exit(0);
}
