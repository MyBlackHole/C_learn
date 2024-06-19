#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define exit_if(r, ...)                                                        \
    if (r)                                                                     \
    {                                                                          \
        printf(__VA_ARGS__);                                                   \
        printf("%s:%d error no: %d error msg %s\n", __FILE__, __LINE__, errno, \
               strerror(errno));                                               \
        exit(EXIT_FAILURE);                                                    \
    }

void server_handle()
{
    int                listenfd;
    int                r;
    ssize_t            ret;
    short              port = 8000;
    struct sockaddr_in addr;
    socklen_t          rsz;

    memset(&addr, 0, sizeof addr);
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    exit_if(listenfd < 0, "create socket error");

    r = bind(listenfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    exit_if(r < 0, "bind socket error");

    r = listen(listenfd, 100);
    exit_if(r < 0, "listen socket error");

    struct sockaddr_in raddr;
    rsz     = sizeof(raddr);
    int cfd = accept(listenfd, (struct sockaddr *)&raddr, &rsz);
    exit_if(cfd < 0, "accept socket error");

    struct sockaddr_in peer;
    socklen_t          alen = sizeof(peer);
    getpeername(cfd, (struct sockaddr *)&peer, &alen);

    printf("accept a connection from %s:%d\n", inet_ntoa(peer.sin_addr),
           ntohs(peer.sin_port));

    printf("but now I will sleep 15 second, then exit\n");

    const int LEN = 1024 * 1000;
    char      msg[LEN];  // 1MB data
    //
    sleep(1);
    ret = read(cfd, msg, LEN);
    exit_if(ret < 0, "read socket error");
    sleep(1);
    ret = write(cfd, msg, ret);
    exit_if(ret < 0, "read socket error");
    getc(stdin);
    exit(EXIT_SUCCESS);
}

int main()
{
    server_handle();

    return EXIT_SUCCESS;
}
