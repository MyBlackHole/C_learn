#include <ctype.h>
#include <stdio.h>

// islower() 用来判断一个字符是否是小写字母，其原型为：
//     int islower(int c);

// 【参数】c 为需要检测的字符。

// 【返回值】若参数c 为小写英文字母，则返回非 0 值，否则返回 0。

// 注意，此为宏定义，非真正函数。

int demo_islower_test_main()
{
	char str[] = "123@#FDsP[e?";
	int index;
	for (index = 0; str[index] != 0; index++) {
		if (islower(str[index])) {
			printf("%c is a lower-case character\n", str[index]);
		}
	}
	return 0;
}
