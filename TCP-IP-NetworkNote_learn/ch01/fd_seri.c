#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1, fd2, fd3;

  char *path = dirname(argv[0]);

  char *filename = "/test.dat";

  char *name = malloc(strlen(path) + strlen(filename));

  strcpy(name, path);
  strcat(name, filename);

  printf("path %s\n", name);

  //创建一个文件和两个套接字
  fd1 = socket(PF_INET, SOCK_STREAM, 0);
  // fd2 = open(name, O_CREAT | O_WRONLY | O_TRUNC);
  fd2 = open(name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
  fd3 = socket(PF_INET, SOCK_DGRAM, 0);
  //输出之前创建的文件描述符的整数值
  printf("file descriptor 1: %d\n", fd1);
  printf("file descriptor 2: %d\n", fd2);
  printf("file descriptor 3: %d\n", fd3);

  free(name);

  close(fd1);
  close(fd2);
  close(fd3);
  return 0;
}
