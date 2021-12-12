#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

// open
// read
// write
int main(int argc, char *argv[]) {

  int sfd = 0, dfd = 0;
  char buf[BUFSIZE] = {0};
  int len = 0, ret = 0;
  int pos = 0;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s <str_file> <desc_file>\n", argv[0]);
    exit(1);
  }

  sfd = open(argv[1], O_RDONLY);
  if (sfd < 0) {
    perror("open()");
    exit(1);
  }

  dfd = open(argv[2], O_WRONLY | O_CREAT, O_TRUNC, 0600);
  if (dfd < 0) {
    close(sfd);
    perror("open()");
    exit(1);
  }

  while (1) {
    len = read(sfd, buf, BUFSIZE);
    if(len < 0) {
      perror("read()");
      exit(1);
    }
    if(len == 0) {
      break;
    }
    pos = 0;
    
    // 需要循环,确保写入 len 字节
    while(len > 0) {
      ret = write(dfd, buf + pos, len);
      if(ret < 0) {
        perror("write()");
        exit(1);
      }
      pos += pos;
      len -= ret;
    }
  }

  close(dfd);
  close(sfd);

  exit(0);
}
