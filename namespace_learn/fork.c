#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int count = 1;
  int child;

  child = fork();

  if (child < 0) {
    perror("fork error : ");
  } else if (child == 0) {
    ++count;
    printf("in child process, pid=%d, count=%d (%p)\n", getpid(), count,
           &count);
  } else {
    ++count;
    printf("in parent process, pid=%d, count=%d (%p)\n", getpid(), count,
           &count);
  }

  printf("pid=%d quit now...\n", getpid());
  return EXIT_SUCCESS;
}
