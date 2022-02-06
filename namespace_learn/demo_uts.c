#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];
char *const child_args[] = {"/bin/bash", NULL};

int child_main(void *args) {
  printf("in child process\n");
  sethostname("NewHostName", 12);
  execv(child_args[0], child_args);
  printf("quit child process¡­\n");
  return 1;
}

int main() {
  printf("start parent process...\n");
  int child_pid =
      clone(child_main, child_stack + STACK_SIZE, CLONE_NEWUTS | SIGCHLD, NULL);
  waitpid(child_pid, NULL, 0);
  printf("quit parent process...\n");
  return 0;
}
