#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buf[80];
  printf("%s\n", getcwd(buf, 80));
  return 0;
}
