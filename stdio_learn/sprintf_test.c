#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char buf[1024];
  int year = 2014, month = 5, day = 13;
  sprintf(buf, "%d-%d-%d", year, month, day);
  puts(buf);
  exit(0);
}
