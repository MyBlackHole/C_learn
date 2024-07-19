/*
 * 变量作用域测试
 */
#include <stdio.h>

int demo_do_while_main()
{
	/* 局部变量定义 */
	int num = 10;

	/* do 循环执行，在条件被测试之前至少执行一次 */
	do {
		printf("a 的值： %d\n", num);
		num = num + 1;
	} while (num < 20);

	return 0;
}
