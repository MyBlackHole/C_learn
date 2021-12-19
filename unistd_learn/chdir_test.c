#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  // 改变工作目录
  if (chdir("/tmp") < 0) {
    perror("chdir error");
    exit(1);
  }

  printf("chdir to /tmp successed\n");

  if (chdir("/tmp/lsp_python.log") < 0) {
    perror("chdir error");
    exit(1);
  }
  exit(0);
}
