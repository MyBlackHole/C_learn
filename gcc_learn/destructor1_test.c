#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_destructor1_main(int argc, char *argv[])
{
	int seconds;
	if (argc < 2) {
		printf("Usage: %s <arg1>\n", argv[0]);
		return EXIT_FAILURE;
	}

	seconds = atoi(argv[1]);

	printf("program pid is %d\n", getpid());
	printf("sleep for %d seconds\n", seconds);
	sleep(seconds);
	return EXIT_SUCCESS;
}

// 程序结束时调用的析构函数
void __attribute__((destructor)) demo_destructor1_func()
{
	printf("%s\n", __FUNCTION__);
}

// xmake run gcc_learn destructor
// out:
// main function
// demo_destructor_func
