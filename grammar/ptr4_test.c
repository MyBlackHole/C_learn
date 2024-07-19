/*
 * 指针测试
 */
#include <stdio.h>
#include <stdlib.h>

int demo_ptr4_main(int argc, char *argv[])
{
	int i_1 = 0;
	int j_1 = 1;
	int *p_1;
	int *p_2;
	int *p_3;
	p_1 = &i_1;
	p_2 = p_1;
	p_3 = &j_1;
	*p_3 = *p_2;
	printf("i = %d\n", i_1);
	printf("p1 = %d\n", *p_1);
	printf("p2 = %d\n", *p_2);
	printf("p3 = %d\n", *p_3);
	exit(0);
}
