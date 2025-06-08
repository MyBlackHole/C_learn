#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	/* 数据类型可以跨平台移植，字节都一样，只要支持C99编译器都可以 */
	int32_t num = 123;
	printf("%ld,%d\n", sizeof(num), num);

	getchar();
	exit(0);
}
