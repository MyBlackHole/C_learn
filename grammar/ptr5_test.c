/*
 * 指针测试
 */
#include <stdio.h>
#include <stdlib.h>

int demo_ptr5_main(int argc, char *argv[])
{
	int i_1 = 2;
	int *p_1 = &i_1;
	int **p__1 = &p_1;
	int *p_2 = *p__1;
	// 值判断
	if (p__1 == NULL) {
		printf("p1 == NULL\n");
	}

	printf("%p\n", &i_1);
	printf("%p\n", p_1);
	printf("%p\n", p_2);
	printf("%p\n", p__1);
	printf("%d\n", **p__1);
	printf("%d\n", *p_2);
	exit(0);
}
