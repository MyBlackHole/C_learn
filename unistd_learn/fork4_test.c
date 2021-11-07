#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void start_fork();

int main(void) {
  start_fork();

  printf("我来了");
  exit(0);
}

static void start_fork() {
  pid_t pid;
  if ((pid = fork()) < 0)
    printf("fork error");
  else if (pid == 0) {
    /* setsid(); */
    printf("child 进来了!!");
  } else {
    printf("child pid:%d\n", pid);
  }
}
