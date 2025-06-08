/*
 * 逻辑测试
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
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
struct test1 {
	/* data */
	int a : 2;
	int b;
} tt_t;

int func9()
{
	struct test1 ttt;
	ttt.b = 9;
	printf("%p\n", &tt_t);
	printf("%p\n", &tt_t.b);
	unsigned long int count =
		(unsigned long int)&tt_t.b - (unsigned long int)&tt_t;
	printf("%lu\n", count);
	printf("%p\n", &ttt);
	printf("%p\n", &ttt.b);
	unsigned long int a_1 = (unsigned long int)&ttt;
	printf("%lu\n", a_1);

	ttt.a = 1;

	// int
	printf("%d\n", *(int *)((unsigned long int)&ttt + count));
	printf("%d\n", ttt.a);
	return 0;
}

int func8()
{
	printf("%p\n", &tt_t);
	printf("%p\n", &tt_t);
	printf("%lu\n", sizeof(tt_t));
	return 0;
}

struct test {
	/* data */
	int a : 2;
};

int func7()
{
	struct test t_1 = { 0 };
	printf("%d\n", t_1.a);
	return 0;
}

int func6()
{
	int i_1 = 1000;
	printf("八进制:%d\n", (i_1));
	return 0;
}

int func5()
{
	int i_1 = 1000;
	printf("八进制:%o\n", i_1);
	printf("十进制:%d\n", i_1);
	printf("十六进制:%X\n", ~0);
	return 0;
}

int func4()
{
	int i_1 = 0;
	// 取反
	printf("%ud", ~i_1);
	return 0;
}

int func3()
{
	int i_1 = 0;
	i_1 &= 1 << 2;
	printf("%d", i_1);
	return 0;
}

int func2()
{
	int i_1 = 0;
	i_1 |= 1 << 2;
	printf("%d", i_1);
	return 0;
}

int func1()
{
	printf("%d\n", 1 ? 1 : 2);
	printf("%d\n", 1 ?: 2);
	printf("%d\n", 0 ?: 2);
	return 0;
	// out:
	// 1
	// 1
	// 2
}

void func10()
{
	if (1) {
		printf("%d\n", 0);
	}
	return;
}

void func11()
{
	int i_1 = 1;
	printf("%d", 1 + --i_1);
}

void func12()
{
	int i_1 = 1;
	printf("%d", 1 + --i_1), printf("ok");
}

void func13()
{
	int i_1 = -1;
	printf("%d\n", i_1 & 256);
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
	char c_1;
	char *str = "abcd";
	c_1 = *str++;
	printf("%c\n", c_1);
	printf("%c\n", *str);
}

void func16()
{
	printf("%ld\n", sizeof(double));
}

void func17()
{
	int a_1;
	double x_1 = 1.1;
	double y_1 = 3.2;
	a_1 = x_1 + y_1;
	printf("%d\n", a_1);
}

void func18()
{
	int test = 1;
	int z_1 = 1;
	printf("%d\n", (++test + z_1++));
}

void func19()
{
	char *str = "abckd";
	printf("%s\n", (str + 3));
}

void func20()
{
	int i = 0;
	printf("%d\n", ++i);
	printf("%d\n", i);
}

int demo_test1_main()
{
	func20();
	// const int a = 0;
	// char c = 'A';
	// printf("111%d\n", a++);
	exit(0);
}
