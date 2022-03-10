#include <assert.h>
#include <signal.h>
#include <stdio.h>

/* 禁用assert */
/* #define NDEBUG */

static void handler(int signal) { printf("触发了-[%d]\n", signal); }

int main() {
  signal(SIGABRT, handler);
  /* signal(SIGABRT, SIG_IGN); */
  // assert(1);
  assert(0);
  printf("正常结束了");
}
