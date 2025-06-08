/*
 * 参数输入测试
 */
#include <stdio.h>
#include <stdlib.h>

int demo_argvs_main(int argc, char *argv[])
{
	for (int i = 0; i < sizeof(argc); i++) {
	}
	printf("%s", argv[0]);
	return EXIT_SUCCESS;
}
