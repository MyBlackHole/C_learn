#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM 80

int demo_getcwd_main(int argc, char *argv[])
{
	char buf[NUM];
	// 获取当前运行目录(工作目录)
	printf("%s\n", getcwd(buf, NUM));
	return EXIT_SUCCESS;
}
