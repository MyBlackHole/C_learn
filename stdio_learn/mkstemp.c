#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void make_temp(char *template);

int main() {
  char good_template[] = "/tmp/dirXXXXXX"; /* right way */
  char *bad_template = "/tmp/dirXXXXXX";   /* wrong way*/

  printf("trying to create first temp file...\n");
  make_temp(good_template);
  printf("trying to create second temp file...\n");
  make_temp(bad_template);
  exit(0);
}

void make_temp(char *template) {
  int fd;
  struct stat sbuf;

  if ((fd = mkstemp(template)) < 0) {
    perror("can't create temp file");
    exit(1);
  }
  printf("temp name = %s\n", template);
  close(fd);
  if (stat(template, &sbuf) < 0) {
    if (errno == ENOENT)
      printf("file doesn't exist\n");
    else {
      perror("stat failed");
      exit(1);
    }
  } else {
    printf("file exists\n");
    unlink(template);
  }
}
