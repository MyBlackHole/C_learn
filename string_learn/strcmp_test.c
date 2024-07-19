#include <stdio.h>
#include <string.h>

#define NUM 10

int demo_strcmp_test_main(int argc, char *argv[])
{
	char str1[NUM];
	char str2[NUM];
	int ret;
	strcpy(str1, "dbcbc");
	strcpy(str2, "bcb");
	ret = strcmp(str1, str2);
	printf("%d\n", ret);
	if (ret > 0) {
		printf("str1 > str2\n");
	} else if (ret < 0) {
		printf("str1 < str2\n");
	} else {
		printf("str1 == str2\n");
	}
	return 0;
}
