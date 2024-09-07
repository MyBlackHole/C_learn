#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/*#define BUFFER_SIZE 165536*/
#define BUFFER_SIZE 65536
/*#define BUFFER_SIZE 4096*/
/*#define BUFFER_SIZE 64*/

inline static int read_is_ready2(int p_fd, const unsigned int time_ms)
{
	int ret = 0;
	struct pollfd fds;
	const int timeout = time_ms;
	memset(&fds, 0x00, sizeof(fds));
	fds.fd = p_fd;
	fds.events = POLLIN;
	if ((ret = poll(&fds, 1, timeout)) < 0) {
		printf("fd: %d, ret: %d, timeout: %d, %s(errno: %d)\n", p_fd,
		       ret, timeout, strerror(errno), errno);
	} else if (fds.revents & POLLIN) {
		return 1;
		/*} else if (fds.revents & (POLLHUP)) {*/
		/*	printf("fd: %d, ret: %d, revents: %d, %s(errno: %d)", p_fd, ret,*/
		/*	       fds.revents, strerror(errno), errno);*/
		/*	return 1;*/
	} else if (fds.revents & (POLLHUP | POLLERR)) {
		printf("fd: %d, ret: %d, revents: %d, %s(errno: %d)\n", p_fd,
		       ret, fds.revents, strerror(errno), errno);
		return -1;
	}
	return 0;
}

int demo_popen_main(int argc, char *argv[])
{
	FILE *p_fp = NULL;
	char buffer[BUFFER_SIZE];
	int64_t nbytes = 0;
	int ready = 0;
	int ret = 0;

	if (argc != 3) {
		printf("Usage: %s test command\n", argv[0]);
		return EXIT_FAILURE;
	}
	p_fp = popen(argv[2], "r");
	if (p_fp == NULL) {
		printf("popen failed: %s(errno: %d)\n", strerror(errno), errno);
		return EXIT_FAILURE;
	}
	/*p_fp = popen("cat /etc/passwd", "r");*/
	// 打印所有内容
	if (strcmp(argv[1], "fgets") == 0) {
		while (fgets(buffer, BUFFER_SIZE, p_fp) != NULL) {
			printf("%s", buffer);
		}
	} else {
		while (1) {
			ready = read_is_ready2(fileno(p_fp), 100);
			if (ready == 1) {
				/*nbytes = fread(buffer, 1, BUFFER_SIZE, p_fp);*/
				nbytes =
					read(fileno(p_fp), buffer, BUFFER_SIZE);
				if (nbytes == 0) {
					break;
				}
				buffer[nbytes] = 0x00;
				printf("%s", buffer);
			} else if (ready == 0) {
			} else {
				printf("pipe close");
				break;
			}
		}
	}

	/*ret = fclose(p_fp);*/
	/*if (ret != 0) {*/
	/*	printf("fclose failed: %s(errno: %d)\n", strerror(errno), errno);*/
	/*	return EXIT_FAILURE;*/
	/*}*/
	/*sleep(30);*/
	ret = pclose(p_fp);
	if (ret != 0) {
		printf("fclose failed: %s(errno: %d)\n", strerror(errno),
		       errno);
		return EXIT_FAILURE;
	}
	sleep(30);
	return EXIT_SUCCESS;
}
