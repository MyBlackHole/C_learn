#include <stdio.h>
#include <stdlib.h>

#define PI 3.14
#define ADD (2 + 3)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char *argv[]) {
  printf("%d\n", ADD * ADD);
  printf("%d\n", MAX(1, 2));
  exit(0);
}
