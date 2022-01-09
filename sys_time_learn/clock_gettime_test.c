#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  struct timespec time1 = {0, 0};
  struct timespec time2 = {0, 0};

  float temp;

  /* 获取时间 */
  clock_gettime(CLOCK_REALTIME, &time1);
  /* 挂起程序 */
  usleep(1000);
  clock_gettime(CLOCK_REALTIME, &time2);
  temp = (time2.tv_nsec - time1.tv_nsec) / 1000000;
  printf("time = %f ms\n", temp);
  return 0;
}
