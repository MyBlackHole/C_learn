#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void error_handling(char *message);

int main(int argc, char *argv[]) {
  int fd;
  char *path = dirname(argv[0]);
  char *filename = "data.txt";
  char *name = malloc(strlen(path) + strlen(filename));

  strcpy(name, path);
  strcat(name, filename);

  char buf[] = "Let's go!\n";
  // O_CREAT | O_WRONLY | O_TRUNC
  // 是文件打开模式，将创建新文件，并且只能写。如存在 data.txt
  // 文件，则清空文件中的全部数据。

  // S_IRUSR | S_IWUSR | S_IXUSR
  // 文件访问权限
  fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
  if (fd == -1) {
    printf("%d--%s\n", errno, strerror(errno));
    error_handling("open() error!");
  }
  printf("file descriptor: %d \n", fd);
  // 向对应 fd 中保存的文件描述符的文件传输 buf 中保存的数据。
  if (write(fd, buf, sizeof(buf)) == -1)
    error_handling("write() error!");
  close(fd);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
