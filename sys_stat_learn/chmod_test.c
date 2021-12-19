#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  struct stat buf;
  if (stat("foo", &buf) < 0)
    perror("stat error for foo");
  if (chmod("foo", (buf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    perror("chmod error for foo");

  if (chmod("bar", S_IRUSR | S_IWUSR | S_IRWXG) < 0)
    perror("chmod error for bar");

  exit(0);
}
