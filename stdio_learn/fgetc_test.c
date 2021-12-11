#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  FILE *fp = NULL;
  int count;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("fopen()");
    exit(1);
  }

  while (fgetc(fp) != EOF) {
    count++;
  }

  fprintf(stdout, "count %d\n", count);

  fclose(fp);

  exit(0);
}
