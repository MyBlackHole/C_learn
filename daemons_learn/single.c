#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

extern int lockfile(int);

int already_running(void) {
  int fd;
  char buf[16];

  fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
  if (fd < 0) {
    syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
    exit(1);
  }
  if (lockfile(fd) < 0) {
    if (errno == EACCES || errno == EAGAIN) {
      close(fd);
      return (1);
    }
    syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
    exit(1);
  }
  ftruncate(fd, 0);
  sprintf(buf, "%ld", (long)getpid());
  write(fd, buf, strlen(buf) + 1);
  return (0);
}
