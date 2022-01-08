#include <stdio.h>
#include <sys/types.h>
// #include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
  sigset_t set;
  // 获取当前信号保存
  sigemptyset(&set);
  printf("set: %lu", set.__val[0]);
  return 0;
}
