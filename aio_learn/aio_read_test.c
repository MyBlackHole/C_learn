#include <aio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int MAX_LIST = 2;

int main(int argc, char **argv) {
  // aio操作所需结构体
  struct aiocb rd;

  int fd, ret, couter;

  fd = open("test.txt", O_RDONLY);
  if (fd < 0) {
    perror("test.txt");
  }

  // 将rd结构体清空
  /* bzero(&rd, sizeof(rd)); */
  memset(&rd, 0, sizeof(rd));

  // 为rd.aio_buf分配空间
  rd.aio_buf = malloc(BUFFER_SIZE + 1);

  // 填充rd结构体
  rd.aio_fildes = fd;
  rd.aio_nbytes = BUFFER_SIZE;
  rd.aio_offset = 0;

  // 进行异步读操作
  ret = aio_read(&rd);
  if (ret < 0) {
    perror("aio_read");
    exit(1);
  }

  couter = 0;
  //  循环等待异步读操作结束
  while (aio_error(&rd) == EINPROGRESS) {
    printf("第%d次: %s\n", ++couter, (char *)rd.aio_buf);
  }

  // 获取异步读返回值
  ret = aio_return(&rd);

  printf("\n\n返回值为:%d", ret);

  return 0;
}
