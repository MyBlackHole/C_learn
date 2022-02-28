#include <errno.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
  int rc;
  rc = syscall(SYS_chmod, "/etc/passwd", 0444);

  if (rc == -1)
    fprintf(stderr, "chmod failed, errno = %d\n", errno);
  else
    printf("chmod succeess!\n");
  return 0;
}
