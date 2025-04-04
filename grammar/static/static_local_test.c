#include <stdio.h>
#include <stdlib.h>

static void test1()
{
	printf("test1\n");
	static int j_1;
	for (int i = 0; i < 5; i++) {
		printf("%d\n", j_1++);
	}
}

static void test2()
{
	printf("test2\n");
	static int j_1;
	for (int i = 0; i < 5; i++) {
		printf("%d\n", j_1++);
	}
}

int demo_static_local_main(int argc, char *argv[])
{
	test1();
	test2();
	test1();
	test2();
	return 0;
}

// 不同函数的局部静态变量互不干扰,
// 因此可以实现不同函数之间的数据隔离,
// 避免函数之间相互影响.
// 同时局部静态变量的生命周期是整个程序运行期间.
// Output:
// ❯ xmake run grammar static_local
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
// test2
// 5
// 6
// 7
// 8
// 9
