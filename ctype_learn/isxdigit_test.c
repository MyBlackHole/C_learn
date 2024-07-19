#include <complex.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// 定义函数：int isxdigit (int c);

// 函数说明：检查参数c是否为16 进制数字，只要c为下列其中一个情况就检测成功。

// 16进制数字：0123456789ABCDEF。

// 返回值：若参数c 为16 进制数字，则返回非 0，否则返回 0。

// 附加说明：此为宏定义，非真正函数。

int demo_isxdigit_test_main()
{
	char str[] = "123c@#FDsP[e?";
	int index;
	for (index = 0; str[index] != 0; index++) {
		if (isxdigit(str[index])) {
			printf("%c is a hexadecimal digits\n", str[index]);
		}
	}
	return EXIT_SUCCESS;
}
