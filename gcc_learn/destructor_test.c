#include <stdio.h>
#include <stdlib.h>

int demo_destructor_main(int argc, char *argv[])
{
	printf("main function\n");
	return EXIT_SUCCESS;
}

// 程序结束时调用的析构函数
void __attribute__((destructor)) demo_destructor_func()
{
	printf("%s\n", __FUNCTION__);
}

// xmake run gcc_learn destructor
// out:
// main function
// demo_destructor_func
