#include <stdio.h>
#include <stdlib.h>

int main() {
  char buffer[50];
  char *s = "runoobcom";
  int i = 1111112;
  int z = 0;
  char port[50];

  // 读取字符串并存储在 buffer 中
  int j = snprintf(buffer, 6, "%s\n", s);

  // 输出 buffer及字符数
  printf("string:\n%s\ncharacter count = %d\n", buffer, j);

  // 读取字符串并存储在 buffer 中
  z = snprintf(port, 6, "%d\n", i);

  // 输出 buffer及字符数
  printf("string:\n%s\ncharacter count = %d\n", port, z);
  exit(0);
}
