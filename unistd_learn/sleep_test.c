#include <unistd.h>
#include <stdio.h>
#include <time.h>


int main() {
  time_t t1 = time((time_t*)NULL);
  printf("start time: %lu\n", t1);
  fflush(stdout);
  sleep(4);
  time_t t2 = time((time_t*)NULL);
  printf("start time: %lu\n", t2);
}
