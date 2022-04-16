#include <ctype.h>
#include <stdio.h>

// 定义函数：int isxdigit (int c);

// 函数说明：检查参数c是否为16 进制数字，只要c为下列其中一个情况就检测成功。

// 16进制数字：0123456789ABCDEF。

// 返回值：若参数c 为16 进制数字，则返回非 0，否则返回 0。

// 附加说明：此为宏定义，非真正函数。

int main() {
  char str[] = "123c@#FDsP[e?";
  int i;
  for (i = 0; str[i] != 0; i++)
    if (isxdigit(str[i]))
      printf("%c is a hexadecimal digits\n", str[i]);
}
