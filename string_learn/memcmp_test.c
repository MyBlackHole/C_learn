/*
 * 比较内存
 */
#include <stdio.h>
#include <string.h>

#define NUM 50

int demo_memcmp_test_main()
{
	/*int ret;*/
	const char src[NUM] = "BlackHole";
	char dest[NUM] = "BlackHole";

	if (memcmp(dest, src, strlen(src)) == 0) {
		printf("相等\n");
	} else {
		printf("不相等\n");
	}
	return (0);
}
