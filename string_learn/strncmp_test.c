#include <stdio.h>
#include <string.h>

#define NUM 15

int demo_strncmp_test_main()
{
	char str1[NUM];
	char str2[NUM];
	int ret;
	strcpy(str1, "abcdef");
	strcpy(str2, "abcdDEF");
	ret = strncmp(str1, str2, 5);
	if (ret < 0) {
		printf("str1 小于 str2");
	} else if (ret > 0) {
		printf("str2 小于 str1");
	} else {
		printf("str1 等于 str2");
	}

	return (0);
}
