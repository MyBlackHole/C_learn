#include <ev.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static ev_timer timer_w1, timer_w2;

void timer_action(struct ev_loop *main_loop, ev_timer *timer_w, int e) {
  time_t now;
  now = time(NULL);
  printf("in tiemr cb%d , cur time is %s\n", timer_w->data, ctime(&now));
}

int main(int argc, char *argv[]) {
  struct ev_loop *main_loop = ev_default_loop(0);

  memset(&timer_w1, 0, sizeof(struct ev_timer));
  memset(&timer_w2, 0, sizeof(struct ev_timer));

  int* i1 = malloc(sizeof(int));
  int* i2 = malloc(sizeof(int));
  *i1 = 1;
  *i2 = 2;

  timer_w1.data = (void *)i1;
  ev_init(&timer_w1, timer_action);
  ev_timer_set(&timer_w1, 10, 5);
  ev_timer_start(main_loop, &timer_w1);

  timer_w2.data = (void *)i2;
  ev_init(&timer_w2, timer_action);
  ev_timer_set(&timer_w2, 5, 10);
  ev_timer_start(main_loop, &timer_w2);

  time_t now;
  now = time(NULL);
  printf("begin time time is %s\n", ctime(&now));

  ev_run(main_loop, 0);
  return 0;
}
