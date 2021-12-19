#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "\tusage:%s <pathname>", argv[0]);
    exit(1);
  }
  if (access(argv[1], R_OK) < 0) {
    fprintf(stderr, "\taccess error for %s", argv[1]);
    exit(1);
  } else
    printf(" \tread access OK\n");

  if (open(argv[1], O_RDONLY) < 0) {
    fprintf(stderr, "\topen error for %s", argv[1]);
    exit(1);

  } else
    printf("\topen for reading OK \n");
  exit(0);
}
