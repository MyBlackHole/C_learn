#include "debug.h"
#include "platform.h"
#include "skiplist.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM (29)
int main() {
  int k;
  char key[SKIP_KSIZE];
  struct slice sk;
  struct skiplist *list = skiplist_new(MAXNUM - 1);

  for (k = 0; k < MAXNUM; k++) {
    snprintf(key, SKIP_KSIZE, "key:%d", k);

    sk.data = key;
    sk.len = SKIP_KSIZE;

    if (skiplist_notfull(list))
      skiplist_insert(list, &sk, k, ADD);
    else
      __DEBUG("%s", "****you need more skiplist...");
  }

  if (MAXNUM < 1000)
    skiplist_dump(list);

  skiplist_free(list);
  return 0;
}
