#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* int poll(struct pollfd *fds, nfds_t nfds, int timeout); */

/*
   struct pollfd {
   int   fd;         // file descriptor
   short events;     // requested events
   short revents;    // returned events
   };
 */

/*
   The  bits that may be set/returned in events and revents are defined in
   <poll.h>:
    POLLIN: There is data to read.(数据可读)
    POLLOUT:Writing now will not block.（数据可读）
 */

#define OPEN_FLAGS O_RDWR | O_CREAT

#define OPEN_MODE 00777

#define W_DATA "howaylee"

#define NUM 12

#define VNAME(value) (#value)

int demo_poll_main(int argc, char *argv[])
{
	ssize_t ret = -1;
	int fd_in = -1;
	int fd_out = -1;
	char r_buf[NUM] = { 0 };
	struct pollfd fds[2] = { 0 };

	fd_in = open(argv[1], OPEN_FLAGS, OPEN_MODE);

	if (-1 == fd_in) {
		fprintf(stderr, "open %s failed: \n", VNAME(fd_in));
		goto _ERR;
	}

	ret = write(fd_in, W_DATA, sizeof(W_DATA));
	if (-1 == ret) {
		fprintf(stderr, "write %s failed: \n", VNAME(fd_in));
		goto _ERR;
	}

	// 设置偏移
	ret = lseek(fd_in, 0, SEEK_SET);
	if (-1 == ret) {
		fprintf(stderr, "lseek %s failed: \n", VNAME(fd_in));
		goto _ERR;
	}

	fd_out = open(argv[2], OPEN_FLAGS, OPEN_MODE);
	if (-1 == fd_out) {
		fprintf(stderr, "open %s failed: \n", VNAME(fd_out));
		goto _ERR;
	}

	/*阻塞，等待程序读写操作*/
	while (1) {
		
		memset(fds, 0x00, sizeof(fds));
		// 初始化pollfd
		// 可读
		// fds[0].fd = 100;
		fds[0].fd = fd_in;
		fds[0].events = POLLIN;

		// 可写
		fds[1].fd = fd_out;
		fds[1].events = POLLOUT;

		// ret = poll(fds, 2, 1000);
		ret = poll(fds, sizeof(fds) / sizeof(fds[0]), -1);
		if (ret < 0) {
			perror("poll failed: ");
			goto _ERR;
		}
		printf("ret = %ld, fds[0].revents = %d, fds[1].revents = %d\n", ret, fds[0].revents, fds[1].revents);

		if (fds[0].revents & POLLNVAL || fds[1].revents & POLLERR)
		{
			perror("poll error: ");
			goto _ERR;
		}

		if (fds[0].revents & POLLIN) {
			// 清空对象内存
			// memset(r_buf, 0, sizeof(r_buf));
			ret = read(fd_in, r_buf, sizeof(r_buf));
			if (ret < 0) {
				perror("poll read failed: ");
				goto _ERR;
			}
			else if (0 == ret) {
				printf("read end of file\n");
				break;
			}
			printf("read = %s\n", r_buf);
		}

		if (fds[1].revents & POLLOUT) {
			ret = write(fd_out, r_buf, sizeof(r_buf));
			if (-1 == ret) {
				perror("poll write failed: ");
				goto _ERR;
			}
			printf("write = %s\n", r_buf);
		}
		sleep(1);
	}

	close(fd_in);
	close(fd_out);

	return EXIT_SUCCESS;
_ERR:
	return EXIT_FAILURE;
}
