// 将字符串复制到数组 dest 中
#include <stdio.h>
#include <string.h>

int main() {
  const char src[50] = "BlackHole";
  char dest[50];

  memcpy(dest, src, strlen(src) + 1);
  printf("dest = %s\n", dest);
  printf("%ld\n", sizeof(void *));
  return (0);
}
