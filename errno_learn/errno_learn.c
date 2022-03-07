#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  fprintf(stderr, "EACCESS :%s\n", strerror(EACCES));
  errno = ENOENT;
  perror(argv[0]);
  exit(0);
}
