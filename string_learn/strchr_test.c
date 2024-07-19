#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int demo_strchr_test_main(int argc, char *argv[])
{
	char *tmp_s;
	char *str = "black,hole";
	// 返回切去 ',' 前字符串
	tmp_s = strchr(str, ',');
	printf("%s\n", tmp_s);
	return EXIT_SUCCESS;
}
