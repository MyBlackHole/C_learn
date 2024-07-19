#include <ctype.h>
#include <stdio.h>

/*
 *
 * 函数说明：检查参数 c 是否为阿拉伯数字0 到9。
 * 返回值：若参数c 为阿拉伯数字，则返回true，否则返回null(0)。
 * 附加说明：此为宏定义，非真正函数。
 *
 */

int demo_isdigit_test_main()
{
	char str[] = "123@#FDsP[e?";
	int index;
	for (index = 0; str[index] != 0; index++) {
		if (isdigit(str[index])) {
			printf("%c is an digit character\n", str[index]);
		}
	}
	return 0;
}
