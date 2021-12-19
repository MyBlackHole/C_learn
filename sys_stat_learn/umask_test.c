#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, char **argv) {
  // 设置mask 返回旧的mask
  umask(0);
  if (creat("foo", RWRWRW) < 0)
    perror("creat error for foo");
  umask(S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH);
  if (creat("bar", RWRWRW) < 0)
    perror("create error for bar");
  exit(0);
}
