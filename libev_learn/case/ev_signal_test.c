#include <ev.h>
#include <stdio.h>

static void sigint_cb(EV_P_ ev_signal *w, int revents) {
  puts("catch SIGINT");
  ev_break(EV_A_ EVBREAK_ALL);
}

int main(void) {
  struct ev_loop *loop = EV_DEFAULT;
  static ev_signal signal_watcher;

  ev_signal_init(&signal_watcher, sigint_cb, SIGINT);
  ev_signal_start(EV_A_ & signal_watcher);

  ev_loop(EV_A_ 0);

  return 0;
}
