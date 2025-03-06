#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

int send_fd(int sock, int fd)
{
	struct msghdr msg = { 0 };
	struct cmsghdr *cmsg;
	char buf[CMSG_SPACE(sizeof(int))];
	char dummy[1] = { '!' }; // 必须发送至少1字节常规数据

	struct iovec io = { .iov_base = dummy, .iov_len = sizeof(dummy) };
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);

	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(int));
	*(int *)CMSG_DATA(cmsg) = fd;

	return sendmsg(sock, &msg, 0);
}

int recv_fd(int sock)
{
	struct msghdr msg = { 0 };
	struct cmsghdr *cmsg;
	char buf[CMSG_SPACE(sizeof(int))];
	char dummy[1];

	struct iovec io = { .iov_base = dummy, .iov_len = sizeof(dummy) };
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);

	if (recvmsg(sock, &msg, 0) <= 0)
		return -1;

	cmsg = CMSG_FIRSTHDR(&msg);
	return *(int *)CMSG_DATA(cmsg);
}

int main()
{
	int sv[2];
	int fd_null = open("/dev/null", O_RDWR);
	if (fd_null < 0) {
		perror("open /dev/null failed");
		exit(1);
	}

	printf("fd_null = %d\n", fd_null);

	if (dup2(fd_null, 2) < 0) {
		perror("dup2 failed");
		exit(1);
	}

	// 等待输入
	printf("Press any key to continue...\n");
	getchar();

	socketpair(AF_UNIX, SOCK_STREAM, 0, sv);

	if (fork() == 0) { // 子进程
		close(sv[0]);
		/*int fd = open("test.txt", O_RDONLY);*/
		send_fd(sv[1], 2);
		printf("send_fd success\n");
		/*close(fd);*/
		exit(0);
	} else { // 父进程
		close(sv[1]);
		int recvfd = recv_fd(sv[0]);
		printf("recvfd = %d\n", recvfd);

		printf("Press any key to continue...\n");
		sleep(100);
		// 使用接收的描述符操作文件
		/*char buf[256];*/
		/*read(recvfd, buf, sizeof(buf));*/
		/*close(recvfd);*/
	}

	wait(NULL);

	close(fd_null);
	return 0;
}

// output:
//
// ❯ ls -alh /proc/430714/fd
// Permissions Size User  Date Modified Name
// lrwx------     - black 28 Feb 13:50   0 -> /dev/pts/7
// lrwx------     - black 28 Feb 13:50   1 -> /dev/pts/7
// lrwx------     - black 28 Feb 13:50   2 -> /dev/null
// lrwx------     - black 28 Feb 13:50   3 -> anon_inode:[eventpoll]
// lrwx------     - black 28 Feb 13:50   4 -> socket:[3975171]
// lrwx------     - black 28 Feb 13:50   5 -> socket:[3975172]
// lrwx------     - black 28 Feb 13:50   6 -> /dev/null
// lrwx------     - black 28 Feb 13:50   7 -> socket:[3960130]
// lrwx------     - black 28 Feb 13:50   8 -> /dev/null
