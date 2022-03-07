#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i = 2;
  int j = 1;
  int *p1 = malloc(sizeof(int) * 2);
  *p1 = i;
  *(p1 + 1) = j;
  int *p2 = malloc(sizeof(int) * 2);
  *p2 = i;
  *(p2 + 1) = j;
  int **pp1 = malloc(sizeof(int *) * 2);
  *pp1 = p1;
  *(pp1 + 1) = p2;
  printf("i = %d\n", *p1);
  printf("j = %d\n", *(p1 + 1));
  printf("pp1-p1 = %d\n", **pp1);
  printf("pp1-p2 = %d\n", *(*(pp1 + 1) + 1));
  printf("pp1:=%p; p2:=%p \n", *(pp1 + 1), p2);
  exit(0);
}
