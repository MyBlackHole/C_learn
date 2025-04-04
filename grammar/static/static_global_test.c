#include <stdio.h>
#include <stdlib.h>

static int ii;
static void test1()
{
	printf("test1\n");
	for (int i = 0; i < 5; i++) {
		printf("%d\n", ii++);
	}
}

static void test3()
{
	printf("test1\n");
	for (int i = 0; i < 5; i++) {
		printf("%d\n", ii++);
	}
}

static void test2()
{
	printf("test2\n");
	static int ii;
	for (int i = 0; i < 5; i++) {
		printf("%d\n", ii++);
	}
}

int demo_static_global_main(int argc, char *argv[])
{
	test1();
	test2();
	test3();
	test1();
	test2();
	test3();
	return 0;
}

// 全局变量 ii 生命周期是整个程序运行期间
// test2 ii 生命周期也是整个程序运行期间
// 但是全局静态变量 ii 与 test2 内的局部变量 ii 互不干扰
// Output:
// ❯ xmake run grammar static_global
// test1
// 0
// 1
// 2
// 3
// 4
// test2
// 0
// 1
// 2
// 3
// 4
// test1
// 5
// 6
// 7
// 8
// 9
// test1
// 10
// 11
// 12
// 13
// 14
// test2
// 5
// 6
// 7
// 8
// 9
// test1
// 15
// 16
// 17
// 18
// 19
