// memchr.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_memchr_test_main()
{
	char *str = "Hello, Programmers test!";
	char *ptr;

	ptr = memchr(str, 'P', strlen(str));
	if (ptr) {
		printf("%s", ptr);
	} else {
		printf("Not Found!");
	}

	// 从标准输入，读取一个字符
	getchar();
	return EXIT_SUCCESS;
}
