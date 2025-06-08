/* SPDX-License-Identifier: MIT */
/*
 * Simple app that demonstrates how to setup an io_uring interface,
 * submit and complete IO against it, and then tear it down.
 *
 * gcc -Wall -O2 -D_GNU_SOURCE -o io_uring-test io_uring-test.c -luring
 */
/*
 * sudo apt install liburing.dev
 */
#define _GNU_SOURCE 1
#include <fcntl.h>
#include <liburing.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define QD 4

int demo_uring_submit_main(int argc, char *argv[])
{
	struct io_uring ring;
	int index;
	int fd_tmp;
	int ret;
	int pending;
	int done;
	struct io_uring_sqe *sqe;
	struct io_uring_cqe *cqe;
	struct iovec *iovecs;
	struct stat sb_s;
	ssize_t fsize;
	off_t offset;
	void *buf;

	if (argc < 2) {
		printf("%s: file\n", argv[0]);
		return 1;
	}

	/*初始化 struct io_uring，函数内部会调用io_uring_queue_init_params。
	* io_uring 是一个循环队列（ring_buffer）。
	* 第一个参数 entries 表示队列大小（实际空间可能比用户指定的大）；
	* 第二个参数 ring 就是需要初始化的 io_uring 结构指针；
	* 第三个参数 flags 是标志参数，无特殊需要传 0 即可。
	* */
	ret = io_uring_queue_init(QD, &ring, 0);
	if (ret < 0) {
		fprintf(stderr, "queue_init: %s\n", strerror(-ret));
		return 1;
	}

	// 打开一个文件
	// O_DIRECT 无缓冲
	fd_tmp = open(argv[1], O_RDONLY | O_DIRECT);
	if (fd_tmp < 0) {
		perror("open");
		return 1;
	}
	/*
	* 获取文件状态信息
	* */
	if (fstat(fd_tmp, &sb_s) < 0) {
		perror("fstat");
		return 1;
	}

	fsize = 0;
	/*
	* 在内存的动态存储区中分配QD个长度为sizeof(struct iovec)的连续空间，
	* 函数返回一个指向分配起始地址的指针；如果分配不成功，返回NULL。
	* */
	iovecs = calloc(QD, sizeof(struct iovec));
	for (index = 0; index < QD; index++) {
		/*
		 * 函数 posix_memalign() 分配大小字节，并将分配的内存地址放在 * memptr
		 * 中。 分配的内存地址将是对齐方式的倍数，必须是 2 的幂和 sizeof(void *)
		 * 的倍数。 如果 size 为 0，则 * memptr 中的值么为 NULL，
		 * 要么为唯一的指针值，以后可以成功将其传递给 free(3)。
		 * posix_memalign() 成功返回零
		 * */
		if (posix_memalign(&buf, 4096, 4096)) {
			return EXIT_FAILURE;
		}
		iovecs[index].iov_base = buf;
		iovecs[index].iov_len = 4096;
		fsize += 4096;
	}

	offset = 0;
	index = 0;
	do {
		/*
		 * io_uring_get_sqe 获取 sqe 结构
		 * 一个 sqe（submission queue entry）代表一次 IO 请求，
		 * 占用循环队列一个空位。
		 * _uring 队列满时 io_uring_get_sqe 会返回 NULL，
		 * 注意错误处理。
		 * */
		sqe = io_uring_get_sqe(&ring);
		if (!sqe) {
			break;
		}
		/*
		 * 初始化 sqe 结构
		 * 第一个参数 sqe 即前面获取的 sqe 结构指针；
		 * fd 为需要读写的文件描述符，可以是磁盘文件也可以是socket；
		 * iovecs 为 iovec 数组，具体使用请参照 readv 和 writev，
		 * nr_vecs 为 iovecs 数组元素个数，
		 * offset 为文件操作的偏移量。
		 * 1代表 io_uring_sqe struct 中的len (buffer size or number of iovecs)
		 * */
		io_uring_prep_readv(sqe, fd_tmp, &iovecs[index], 1, offset);
		offset += iovecs[index].iov_len;
		index++;
		if (offset > sb_s.st_size) {
			break;
		}
	} while (1);
	/*
	* 准备好 sqe 后即可使用 io_uring_submit 提交请求。
	* 可以一次性初始化多个 sqe 然后一次性 submit。
	* */
	ret = io_uring_submit(&ring);
	if (ret < 0) {
		fprintf(stderr, "io_uring_submit: %s\n", strerror(-ret));
		return 1;
	} else if (ret != index) {
		fprintf(stderr, "io_uring_submit submitted less %d\n", ret);
		return 1;
	}

	done = 0;
	pending = ret;
	fsize = 0;
	for (index = 0; index < pending; index++) {
		/*
		 * 获取当前已完成的 IO 操作。会阻塞线程，等待 IO 操作完成。
		 * */
		ret = io_uring_wait_cqe(&ring, &cqe);
		if (ret < 0) {
			fprintf(stderr, "io_uring_wait_cqe: %s\n",
				strerror(-ret));
			return 1;
		}

		done++;
		ret = 0;
		if (cqe->res != 4096 && cqe->res + fsize != sb_s.st_size) {
			fprintf(stderr, "ret=%d, wanted 4096\n", cqe->res);
			ret = 1;
		}
		fsize += cqe->res;
		/*
		 * 默认情况下 IO 完成事件不会从队列中清除，
		 * 导致 io_uring_peek_cqe 会获取到相同事件，
		 * 使用 io_uring_cqe_seen 标记该事件已被处理
		 * */
		io_uring_cqe_seen(&ring, cqe);
		if (ret) {
			break;
		}
	}

	printf("Submitted=%d, completed=%d, bytes=%lu\n", pending, done,
	       (unsigned long)fsize);
	close(fd_tmp);
	/*
	* 清除 io_uring 结构
	* */
	io_uring_queue_exit(&ring);
	return 0;
}
