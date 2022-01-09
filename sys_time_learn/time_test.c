#include <stdio.h>
#include <time.h>


int main() {
  time_t t1 = time((time_t*)NULL);
  printf("start time: %lu", t1);
}
