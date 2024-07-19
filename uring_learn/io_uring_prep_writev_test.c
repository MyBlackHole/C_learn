#include <fcntl.h>
#include <liburing.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int demo_io_uring_prep_writev_main(int argc, char **argv)
{
	if (argc < 2) {
		printf("%s: file\n", argv[0]);
		return 1;
	}

	struct io_uring ring;
	io_uring_queue_init(32, &ring, 0);

	// 获取一个 sqe
	struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);

	// 打开一个文件
	int fd_tmp = open(argv[1], O_WRONLY | O_CREAT);

	struct iovec iov = {
		.iov_base = "Hello world",
		.iov_len = strlen("Hello world"),
	};

	// 初始化 sqe 写
	io_uring_prep_writev(sqe, fd_tmp, &iov, 1, 0);
	// 提交写
	io_uring_submit(&ring);

	struct io_uring_cqe *cqe;

	for (;;) {
		io_uring_peek_cqe(&ring, &cqe);
		if (!cqe) {
			puts("Waiting...");
			// accept 新连接，做其他事
		} else {
			puts("Finished.");
			break;
		}
	}
	io_uring_cqe_seen(&ring, cqe);
	io_uring_queue_exit(&ring);
	return EXIT_SUCCESS;
}
