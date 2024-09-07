/*
 * 日志
 * 参数测试
 */
#include <stdlib.h>
#include <stdio.h>

#define Logf(SERVER_ID, FORMAT, ...) \
	printf("%d: " FORMAT "\n", SERVER_ID, __VA_ARGS__)

int demo_VA_ARGS_main(int argc, char *argv[])
{
	Logf(1, "main %d", 1);
	return EXIT_SUCCESS;
}
