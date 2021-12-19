#include <stdio.h>

struct A {
  int a;
  int b;
};

int main() {
  struct A a1 = {.a = 2, .b = 3};
  printf("a1.a--%d\n", a1.a);

  struct A a2 = {a : 3, b : 4};
  printf("a2.a--%d\n", a2.a);
  return 0;
}
