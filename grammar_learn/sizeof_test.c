#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *p2 = malloc(1000);
  // 无法获取 malloc 空间大小
  printf("%ld\n", sizeof(*p2));
  exit(0);
}
