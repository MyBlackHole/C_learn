#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destroy_string(char **str)
{
	printf("final str : %s\n", *str);
	free(*str);
}

int demo_cleanup_main(int argc, char **argv)
{
	// 作用域结束(return goto break ...)后自动释放
	char *str __attribute__((__cleanup__(destroy_string))) = NULL;
	str = (char *)malloc((sizeof(char)) * 100);
	strcpy(str, "hello world!");
	printf("current str : %s\n", str);
	return 0;
}

// out:
// current str : hello world
// final str : hello world
