#include <ctype.h>
#include <stdio.h>

/*
 *
 * 函数说明：检查参数 c 是否为阿拉伯数字0 到9。
 * 返回值：若参数c 为阿拉伯数字，则返回true，否则返回null(0)。
 * 附加说明：此为宏定义，非真正函数。
 *
 */

int main() {
  char str[] = "123@#FDsP[e?";
  int i;
  for (i = 0; str[i] != 0; i++)
    if (isdigit(str[i]))
      printf("%c is an digit character\n", str[i]);
}
