#include <stdio.h>
#include <stdlib.h>

int demo_attribute_main(int argc, char *argv[])
{
	printf("main function\n");
	return EXIT_SUCCESS;
}

// 程序启动后会直接执行
// __attribute__((constructor(102)))
__attribute__((constructor)) static void beforeFunction()
{
	printf("beforeFunction\n");
}

// out: (比 main 开先)
// beforeFunction
// main function
