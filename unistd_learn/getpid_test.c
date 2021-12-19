#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("getpid_test.c from process Id %ld\n", (long)getpid());
  exit(0);
}
