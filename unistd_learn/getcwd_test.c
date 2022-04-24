#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buf[80];
  // 获取当前运行目录
  printf("%s\n", getcwd(buf, 80));
  return 0;
}
