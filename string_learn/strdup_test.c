#include <stdio.h>
#include <string.h>

int main() {
  char a[] = "strdup";
  char *b;
  b = strdup(a);
  printf("b[]=\"%s\"\n", b);
}
