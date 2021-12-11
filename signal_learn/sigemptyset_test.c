#include <sys/types.h>
#include <stdio.h>
// #include <unistd.h>
#include <signal.h>

int main (int argc, char *argv[])
{
  sigset_t set;
  sigemptyset(&set);
  printf("set: %lu", set.__val[0]);
  return 0;
}
