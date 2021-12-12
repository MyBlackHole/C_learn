#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FNAME "/tmp/out"

int main(int argc, char *argv[]) {
  int fd = 0, dfd = 0;
  int status = 0;
  fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if (fd < 0) {
    perror("open()");
    exit(1);
  }

  status = close(1);
  if (status < 0) {
    perror("close()");
    exit(1);
  }

  dfd = dup(fd);
  if (dfd < 0) {
    perror("dup()");
    exit(1);
  }
  close(fd);
  puts("black");
  exit(0);
}
