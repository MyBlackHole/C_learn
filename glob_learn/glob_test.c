#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int errfunc(const char *errpath, int errno) {
  puts(errpath);
  fprintf(stderr, "ERROR MSG%s\n", strerror(errno));
  return 0;
}

// 执行
// ./out/obj/glob_learn/glob_test '/*'

int main(int argc, char *argv[]) {
  glob_t globres;
  int err;
  int i;

  if (argc < 2) {
    fprintf(stderr, "<str>");
    exit(1);
  }

  // err = glob(argv[1], 0, NULL, &globres);
  err = glob(argv[1], 0, errfunc, &globres);
  if (err) {
    fprintf(stderr, "ERROR %d\n", err);
    exit(1);
  }

  for (i = 0; i < globres.gl_pathc; i++) {
    puts(globres.gl_pathv[i]);
  }
  globfree(&globres);
  return 0;
}
