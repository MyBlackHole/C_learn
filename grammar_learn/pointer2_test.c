#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i = 2;
  int *p = &i;
  int **p1 = &p;
  int *p2 = *p1;
  // 值判断
  if (p1 == NULL) {
    printf("p1 == NULL\n");
  }

  printf("%p\n", &i);
  printf("%p\n", p);
  printf("%p\n", p2);
  printf("%p\n", p1);
  printf("%d\n", **p1);
  printf("%d\n", *p2);
  exit(0);
}
