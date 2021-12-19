#include <stdio.h>

int main() {
#define MAX 200
  printf("MAX = %d\n", MAX);
#undef MAX

  int MAX = 10;
  printf("MAX = %d\n", MAX);

  return 0;
}

/******** 例程1：main.c ********/
