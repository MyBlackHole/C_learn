#include <stdio.h>
#include <string.h>

#define NUM 15

int demo_strcoll_test_main()
{
	char str1[NUM];
	char str2[NUM];
	int ret;

	strcpy(str1, "abc");
	strcpy(str2, "ABC");

	ret = strcoll(str1, str2);

	if (ret > 0) {
		printf("str1 大于 str2\n");
	} else if (ret < 0) {
		printf("str2 小于 str1\n");
	} else {
		printf("str1 等于 str2\n");
	}

	return (0);
}
