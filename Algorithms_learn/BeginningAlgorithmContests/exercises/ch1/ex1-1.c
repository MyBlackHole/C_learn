/*
  习题1-1. 平均数（average）
  刘汝佳
*/

#include <stdio.h>
int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  printf("%.3lf\n", (a + b + c) / 3.0);
  return 0;
}
