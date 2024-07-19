/*
 * 测试解析
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int demo_pg_summary_main(int argc, char *argv[])
{
	uint32_t tmp[5];
	char *name = "000000010000000008000028000000000A000028.summary";
	sscanf(name, "%08X%08X%08X%08X%08X", &tmp[0], &tmp[1], &tmp[2], &tmp[3],
	       &tmp[4]);
	printf("%d %d %d %d %d\n", tmp[0], tmp[1], tmp[2], tmp[3], tmp[4]);
	return EXIT_SUCCESS;
}
