#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = 0;
  if (argc < 2) {
    fprintf(stderr, "<path>\n");
    exit(1);
  }

  fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
  lseek(fd, 5LL * 1024LL * 1024LL * 1024LL - 1LL, SEEK_SET);

  write(fd, "", 1);

  close(fd);

  exit(0);
}
