#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("getppid_test.c from process Id %ld\n", (long)getppid());
  exit(0);
}
