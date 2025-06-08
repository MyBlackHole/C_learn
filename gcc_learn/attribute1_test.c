#include <stdio.h>
#include <stdlib.h>

int demo_attribute1_main(int argc, char *argv[])
{
	printf("main function\n");
	return EXIT_SUCCESS;
}

// 程序启动后会直接执行
static __attribute__((constructor(101))) void before1()
{
	printf("before1\n");
}
static __attribute__((constructor(102))) void before2()
{
	printf("before2\n");
}
static __attribute__((constructor(102))) void before3()
{
	printf("before3\n");
}

// out: (比 main 开先)
// beforeFunction
// main function
