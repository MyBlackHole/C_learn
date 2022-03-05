#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char str1[10];
  char str2[10];
  int ret;
  strcpy(str1, "dbcbc");
  strcpy(str2, "bcb");
  ret = strcmp(str1, str2);
  printf("%d\n", ret);
  if (ret > 0) {
    printf("str1 > str2\n");
  } else if (ret < 0) {
    printf("str1 < str2\n");
  } else {
    printf("str1 == str2\n");
  }
  return 0;
}
