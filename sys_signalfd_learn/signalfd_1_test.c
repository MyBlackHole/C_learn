#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <unistd.h>

#define NUM 1024

void signalCallBackFunc(int signalFd)
{
	struct signalfd_siginfo fd_siginfo;
	printf("signalCallBackFunc\n");
	read(signalFd, &fd_siginfo, sizeof(struct signalfd_siginfo));
	printf("signal %d received\n", fd_siginfo.ssi_signo);
	printf("pid %d, uid %d, fd %d\n", fd_siginfo.ssi_pid,
	       fd_siginfo.ssi_uid, fd_siginfo.ssi_fd);
}

int demo_signalfd_1_main()
{
	printf("%d\n", getpid());
	int epfd = epoll_create1(0);
	int num;
	sigset_t sigint_mask;

	sigemptyset(&sigint_mask);
	sigaddset(&sigint_mask, SIGINT);
	sigprocmask(SIG_BLOCK, &sigint_mask, NULL);

	int sigintfd;
	sigintfd = signalfd(-1, &sigint_mask, 0);

	struct epoll_event sigint_event;
	sigint_event.data.fd = sigintfd;
	sigint_event.events = EPOLLIN;

	// 添加监控
	epoll_ctl(epfd, EPOLL_CTL_ADD, sigintfd, &sigint_event);

	struct epoll_event events[NUM];
	while (1) {
		// 等待事件
		num = epoll_wait(epfd, events, NUM, -1);

		for (int i = 0; i < num; i++) {
			int returnfd = events[i].data.fd;
			signalCallBackFunc(returnfd);

			// epoll_ctl(epfd, EPOLL_CTL_DEL, returnfd, NULL);
		}
	}
}

// out:
// xmake run sys_signalfd_learn signalfd_1
//
// kill -n 2 33162
//
// signalCallBackFunc
// signal 2 received
// pid 32803, uid 1000, fd 0
