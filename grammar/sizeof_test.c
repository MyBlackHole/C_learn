#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 1000

int demo_sizeof_main(int argc, char *argv[])
{
	char *str = "1234567891000";
	int *test = malloc(NUM);
	// 无法获取 malloc 空间大小
	//
	// 此是获取一个 int 大小
	printf("*p2-%ld\n", sizeof(*test));
	// 此是获取一个 int* 大小
	printf("p2-%ld\n", sizeof(test));

	// 此是获取一个 char* 大小
	printf("*str-%ld\n", strlen(str));

	// 此是获取一个字符串大小
	printf("strlen(str)-%ld\n", strlen(str));
	exit(0);
}

// out:
// *p2-4
// p2-8
// *str-8
// strlen(str)-13
