#include <ctype.h>
#include <stdio.h>

// islower() 用来判断一个字符是否是小写字母，其原型为：
//     int islower(int c);

// 【参数】c 为需要检测的字符。

// 【返回值】若参数c 为小写英文字母，则返回非 0 值，否则返回 0。

// 注意，此为宏定义，非真正函数。

int main()
{
    char str[] = "123@#FDsP[e?";
    int i;
    for (i = 0; str[i] != 0; i++)
        if (islower(str[i]))
            printf("%c is a lower-case character\n", str[i]);
}
