//
// Created by shengym on 2019-07-07.
//

#ifndef YOLANDA_COMMON_H
#define YOLANDA_COMMON_H

#include "config.h"

#include "channel_map.h"
#include "inetaddress.h"
#include "log.h"
#include "tcp_server.h"
#include <netdb.h>


void err_dump(const char *, ...);

void err_msg(const char *, ...);

void err_quit(const char *, ...);

void err_ret(const char *, ...);

void err_sys(const char *, ...);

void error(int status, int err, char *fmt, ...);

char *sock_ntop(const struct sockaddr_in *sin, socklen_t salen);

size_t readn(int fd, void *vptr, size_t n);

size_t read_message(int fd, char *buffer, size_t length);

size_t readline(int fd, char *buffer, size_t length);

int tcp_server(int port);

int tcp_server_listen(int port);

int tcp_nonblocking_server_listen(int port);

void make_nonblocking(int fd);

int tcp_client(char *address, int port);

#define SERV_PORT 43211
#define MAXLINE 4096
#define UNIXSTR_PATH "/var/lib/unixstream.sock"
#define LISTENQ 1024
#define BUFFER_SIZE 4096

#endif // YOLANDA_COMMON_H
