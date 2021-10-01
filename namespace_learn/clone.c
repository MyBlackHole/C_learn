#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024*1024)

static char child_stack[STACK_SIZE];

int child_main(void * args) {
   printf("in child process, pid=%d\n", getpid());
printf("quit child process...\n");
   return EXIT_SUCCESS;
}

int main(){
   printf("start...\n");
   printf("in parent process, pid=%d\n", getpid());
   int child_pid = clone(child_main, child_stack + STACK_SIZE, SIGCHLD, NULL);
   waitpid(child_pid, NULL, 0);
   printf("quit...\n");
   return EXIT_SUCCESS;
}
