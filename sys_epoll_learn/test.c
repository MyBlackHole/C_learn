#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_EVENT 20
#define READ_BUF_LEN 256

/**
 * 设置 file describe 为非阻塞模式
 * @param fd 文件描述
 * @return 返回0成功，返回-1失败
 */
static int make_socket_non_blocking(int fd)
{
	int flags, s;
	// 获取当前flag
	flags = fcntl(fd, F_GETFL, 0);
	if (-1 == flags) {
		perror("Get fd status");
		return -1;
	}

	flags |= O_NONBLOCK;

	// 设置flag
	s = fcntl(fd, F_SETFL, flags);
	if (-1 == s) {
		perror("Set fd status");
		return -1;
	}
	return 0;
}

int main()
{
	// epoll 实例 file describe
	int epfd = 0;
	int listenfd = 0;
	int result = 0;
	struct epoll_event ev, event[MAX_EVENT];
	// 绑定的地址
	const char *const local_addr = "192.168.5.60";
	struct sockaddr_in server_addr = { 0 };

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listenfd) {
		perror("Open listen socket");
		return -1;
	}
	/* Enable address reuse */
	int on = 1;
	// 打开 socket 端口复用, 防止测试的时候出现 Address already in use
	result =
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (-1 == result) {
		perror("Set socket");
		return 0;
	}

	server_addr.sin_family = AF_INET;
	inet_aton(local_addr, &(server_addr.sin_addr));
	server_addr.sin_port = htons(8080);
	result = bind(listenfd, (const struct sockaddr *)&server_addr,
		      sizeof(server_addr));
	if (-1 == result) {
		perror("Bind port");
		return 0;
	}
	result = make_socket_non_blocking(listenfd);
	if (-1 == result) {
		return 0;
	}

	result = listen(listenfd, 200);
	if (-1 == result) {
		perror("Start listen");
		return 0;
	}

	// 创建epoll实例
	epfd = epoll_create1(0);
	if (1 == epfd) {
		perror("Create epoll instance");
		return 0;
	}

	ev.data.fd = listenfd;

	/* 边缘触发选项。 */;
	ev.events = EPOLLIN | EPOLLET;

	// 设置epoll的事件
	result = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

	if (-1 == result) {
		perror("Set epoll_ctl");
		return 0;
	}

	for (;;) {
		int wait_count;
		// 等待事件
		wait_count = epoll_wait(epfd, event, MAX_EVENT, -1);

		for (int i = 0; i < wait_count; i++) {
			uint32_t events = event[i].events;
			// IP地址缓存
			char host_buf[NI_MAXHOST];
			// PORT缓存
			char port_buf[NI_MAXSERV];

			int __result;
			// 判断epoll是否发生错误
			if (events & EPOLLERR || events & EPOLLHUP ||
			    ((!events) & EPOLLIN)) {
				printf("Epoll has error\n");
				close(event[i].data.fd);
				continue;
			} else if (listenfd == event[i].data.fd) {
				// listen的 file describe 事件触发， accpet事件
				// 由于采用了边缘触发模式，这里需要使用循环
				for (;;) {
					struct sockaddr in_addr = { 0 };
					socklen_t in_addr_len = sizeof(in_addr);
					int accp_fd = accept(listenfd, &in_addr,
							     &in_addr_len);
					if (-1 == accp_fd) {
						perror("Accept");
						break;
					}
					__result = getnameinfo(
						&in_addr, sizeof(in_addr),
						host_buf,
						sizeof(host_buf) /
							sizeof(host_buf[0]),
						port_buf,
						sizeof(port_buf) /
							sizeof(port_buf[0]),
						NI_NUMERICHOST |
							NI_NUMERICSERV);

					if (!__result) {
						printf("New connection: host = %s, port = %s\n",
						       host_buf, port_buf);
					}

					__result = make_socket_non_blocking(
						accp_fd);
					if (-1 == __result) {
						return 0;
					}

					ev.data.fd = accp_fd;
					ev.events = EPOLLIN | EPOLLET;
					// 为新accept的 file describe 设置epoll事件
					__result = epoll_ctl(epfd,
							     EPOLL_CTL_ADD,
							     accp_fd, &ev);

					if (-1 == __result) {
						perror("epoll_ctl");
						return 0;
					}
				}
				continue;
			} else {
				// 其余事件为 file describe 可以读取
				int done = 0;
				// 因为采用边缘触发，所以这里需要使用循环。如果不使用循环，程序并不能完全读取到缓存区里面的数据。
				for (;;) {
					ssize_t result_len = 0;
					char buf[READ_BUF_LEN] = { 0 };

					result_len = read(
						event[i].data.fd, buf,
						sizeof(buf) / sizeof(buf[0]));

					if (-1 == result_len) {
						if (EAGAIN != errno) {
							perror("Read data");
							done = 1;
						}
						break;
					} else if (!result_len) {
						done = 1;
						break;
					}

					write(STDOUT_FILENO, buf, result_len);
				}
				if (done) {
					printf("Closed connection\n");
					close(event[i].data.fd);
				}
			}
		}
	}
	close(epfd);
	return 0;
}
