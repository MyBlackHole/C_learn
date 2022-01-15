#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  time_t t;
  t = time(NULL);
  printf("%ld\n", t);
  return 0;
}
