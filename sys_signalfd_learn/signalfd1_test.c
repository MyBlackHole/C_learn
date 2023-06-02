#include <signal.h>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void signalCallBackFunc(int signalFd)
{
    struct signalfd_siginfo fdsiI;
    printf("signalCallBackFunc\n");
    read(signalFd, &fdsiI, sizeof(struct signalfd_siginfo));
}

int main()
{
    printf("%d\n", getpid());
    int epfd = epoll_create1(0);
    sigset_t sigintMask;

    sigemptyset(&sigintMask);
    sigaddset(&sigintMask, SIGINT);
    sigprocmask(SIG_BLOCK, &sigintMask, NULL);

    int sigintfd;
    sigintfd = signalfd(-1, &sigintMask, 0);

    struct epoll_event sigintEvent;
    sigintEvent.data.fd = sigintfd;
    sigintEvent.events = EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, sigintfd, &sigintEvent);

    struct epoll_event events[1024];
    while (1)
    {
        int n = epoll_wait(epfd, events, 1024, -1);

        for (int i = 0; i < n; i++)
        {
            int returnfd = events[i].data.fd;
            signalCallBackFunc(returnfd);
        }
    }
}
