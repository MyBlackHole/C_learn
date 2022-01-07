#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
  int serv_sock;
  int clnt_sock;

  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size;

  char message[] = "Hello World!";

  if (argc != 2) {
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }
  //调用 socket 函数创建套接字
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1)
    error_handling("socket() error");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  //调用 bind 函数分配ip地址和端口号
  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    error_handling("bind() error");

  printf("42");
  //调用 listen 函数将套接字转为可接受连接状态
  if (listen(serv_sock, 5) == -1)
    error_handling("listen() error");

  clnt_addr_size = sizeof(clnt_addr);

  while (1) {
    printf("48");
    //调用 accept 函数受
    //连接请求。如果在没有连接请求的情况下调用该函数，则不会返回，直到有连接请求为止
    clnt_sock =
        accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

    if (clnt_sock == -1) {
      perror("accept() error");
      sleep(2);
      continue;
    }

    int flags = fcntl(serv_sock, F_GETFL, 0);
    if (flags < 0) {
      perror("fcntl");
      return -1;
    }

    flags |= O_NONBLOCK;
    fcntl(clnt_sock, F_SETFL, flags);

    //稍后要将介绍的 write 函数用于传输数据，若程序经过 accept
    //这一行执行到本行，则说明已经有了连接请求
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
  }
  close(serv_sock);
  return 0;
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
