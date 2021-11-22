#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int num) { printf("\nrecvive the signal is %d\n", num); }

int main() {
  int time = 20;

  signal(SIGINT, sig_handler);
  printf("enter to the sleep.\n");

  /* #<{(| 会被中断，然后直接执行下一行 |)}># */
  /* sleep(time); */

  /* 这样才能确保堵塞 time 时间 */
  do {
    printf("还有 %d 秒", time);
    time = sleep(time);
  } while (time > 0);

  printf("sleep is over, main over.\n");

  exit(0);
}
