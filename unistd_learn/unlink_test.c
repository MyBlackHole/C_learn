#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (open("tempfile", O_RDWR) < 0) {
    perror("open tempfile file faied");
    exit(1);
  }
  if (unlink("tempfile") < 0) {
    perror("unlink error");
    exit(1);
  }
  printf("file unlinked \n");
  sleep(10);
  printf("done\n");
  exit(0);
}
