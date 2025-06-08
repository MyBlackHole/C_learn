#include <stdio.h>

#define TEST_PATH "ok"

int demo_define1_main(int argc, char *argv[])
{
	char str[100] = "a" TEST_PATH;
	printf("str = %s\n", str);
	return 0;
}
