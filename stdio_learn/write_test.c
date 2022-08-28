#include <stdio.h>
#include <unistd.h>

int main(void) {
  putchar('a');
  write(STDOUT_FILENO, "b", 1);
  putchar('a');
  write(STDOUT_FILENO, "b", 1);
  putchar('a');
  write(STDOUT_FILENO, "b", 1);

  printf("\n");
  return 0;
}
// window 下生成ababab
// linux下是bbbaaa
