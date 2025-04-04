/*
 * 指针测试
 */
#include <stdio.h>
#include <stdlib.h>

int demo_ptr3_main(int argc, char *argv[])
{
	int i_1 = 2;
	int j_1 = 1;
	int *p_1 = malloc(sizeof(int) * 2);
	*p_1 = i_1;
	*(p_1 + 1) = j_1;
	int *p_2 = malloc(sizeof(int) * 2);
	*p_2 = i_1;
	*(p_2 + 1) = j_1;
	int **pp1 = malloc(sizeof(int *) * 2);
	*pp1 = p_1;
	*(pp1 + 1) = p_2;
	printf("i = %d\n", *p_1);
	printf("j = %d\n", *(p_1 + 1));
	printf("pp1-p1 = %d\n", **pp1);
	printf("pp1-p2 = %d\n", *(*(pp1 + 1) + 1));
	printf("pp1:=%p; p2:=%p \n", *(pp1 + 1), p_2);
	exit(0);
}
