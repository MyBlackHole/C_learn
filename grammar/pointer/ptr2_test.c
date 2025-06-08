/*
 * 指针测试
 */
#include <stdio.h>

int demo_ptr2_main(void)
{
	char *ptr = "Linux";
	printf("%c\n", *ptr++);
	printf("%c\n", *ptr);
	return 0;
}
