#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = -1;
  FILE *file = NULL;
  file = fopen("BUILD.gn", "rb");
  if (file == NULL) {
    perror(strerror(errno));
    exit(1);
  }
  fd = fileno(file);
  close(fd);
  fclose(file);
  printf("%d\n", fd);
  exit(0);
}
