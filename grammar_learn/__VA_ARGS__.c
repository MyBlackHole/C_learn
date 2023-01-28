#include <stdio.h>
#include <stdlib.h>

#define Logf(SERVER_ID, FORMAT, ...)                                           \
  printf("%d: " FORMAT "\n", SERVER_ID, __VA_ARGS__)

int main(int argc, char *argv[]) {
  Logf(1, "main %d", 1);
  return 0;
}
