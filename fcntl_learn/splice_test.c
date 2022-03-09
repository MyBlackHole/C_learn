#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// SPLICE_F_NONBLOCK：splice 操
// 不会被阻塞。然而，如果文件描述符没有被设置为不可被阻塞方式的 I/O
// ，那么调用 splice 有可能仍然被阻塞。 SPLICE_F_MORE：告知操作系统内核下一个
// splice 系统调用将会有更多的数据传来。
// SPLICE_F_MOVE：如果输出是文件，这个值则会使得操作系统内核尝试从输入管道缓冲区直接将数据读入到输出地址空间，这个数据传输过程没有任何数据拷贝操作发生。

// 使用splice时， fd_in和fd_out中必须至少有一个是管道文件描述符。
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s <file>\n", argv[0]);
    return 1;
  }
  int filefd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
  assert(filefd > 0);

  int pipefd_stdout[2];
  int ret = pipe(pipefd_stdout);
  assert(ret != -1);

  int pipefd_file[2];
  ret = pipe(pipefd_file);
  assert(ret != -1);

  ret = splice(STDIN_FILENO, NULL, pipefd_stdout[1], NULL, 32768,
               SPLICE_F_MORE | SPLICE_F_MOVE);
  assert(ret != -1);

  ret = tee(pipefd_stdout[0], pipefd_file[1], 32768, SPLICE_F_NONBLOCK);
  assert(ret != -1);
  ret = splice(pipefd_file[0], NULL, filefd, NULL, 32768,
               SPLICE_F_MORE | SPLICE_F_MOVE);
  assert(ret != -1);

  ret =
      splice(pipefd_stdout[0], NULL, STDOUT_FILENO, NULL, 32768, SPLICE_F_GIFT);
  printf("errno:%d\n", errno);

  assert(ret != -1);

  close(filefd);
  close(pipefd_stdout[0]);
  close(pipefd_stdout[1]);
  close(pipefd_file[0]);
  close(pipefd_file[1]);
  return 0;
}
