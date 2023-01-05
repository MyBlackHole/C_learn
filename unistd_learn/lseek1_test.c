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

  fd = open(argv[1], O_RDONLY);
  lseek(fd, 1, SEEK_SET);

  // write(fd, "ok", 3);
  int n = 10;
  char *s = malloc(n);
  read(fd, s, n);
  printf("%s\n", s);

  close(fd);

  exit(0);
}
