#include <stdio.h>
#include <stdlib.h>

#if 0
#define MAX(i, j) ((i) > (j) ? (i) : (j))

#else
#define MAX(i, j)                                                              \
  ({                                                                           \
    int A = i, B = j;                                                          \
    (A) > (B) ? (A) : (B);                                                     \
  })
int max(int a, int b) { return a > b ? a : b; }
#endif

int main(int argc, char *argv[]) {
  int i = 5, j = 3;

  int k;

  printf("i = %d\tj = %d\n", i, j);
  printf("%d\n", MAX(i++, j++));
  printf("i = %d\tj = %d\n", i, j);
  exit(0);
}
