#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define NUM 64

void my_sleep()
{
    while (true)
    {
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int ret;
    char client_addr[INET_ADDRSTRLEN];
    int client_fd;
    int listen_fd;
    int pid;
    struct in_addr ip_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        fprintf(stderr, "Create Socket Error, errno:%s\n", strerror(errno));
        goto ERR;
    }
    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    ret =
        bind(listen_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        fprintf(stderr, "Bind Error, errno:%s\n", strerror(errno));
        goto ERR;
    }

    ret = listen(listen_fd, NUM);
    if (ret < 0)
    {
        fprintf(stderr, "Listen Error, errno:%s\n", strerror(errno));
        goto ERR;
    }

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork Error, errno:%s\n", strerror(errno));
        goto ERR;
    }

    if (pid == 0)
    {
        // setsid();
        close(listen_fd);
        fprintf(stdout, "client, pid:%d\n", getpid());
        my_sleep();
        goto RET;
    }

    fprintf(stdout, "parent, pid:%d\n", getpid());

    while (1)
    {
        struct sockaddr_in cli;
        socklen_t len = sizeof(struct sockaddr_in);
        client_fd = accept(listen_fd, (struct sockaddr *)&cli, &len);
        ip_addr = cli.sin_addr;
        inet_ntop(AF_INET, &ip_addr, client_addr, INET_ADDRSTRLEN);
        printf("Client Address is : %s\n", client_addr);
        close(client_fd);
    }
RET:
    return EXIT_SUCCESS;

ERR:
    close(listen_fd);
    return EXIT_FAILURE;
}
