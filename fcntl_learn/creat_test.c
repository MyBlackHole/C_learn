#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OFFSET 16384

char buf1[] = "qwertyuiop";
char buf2[] = "QWERTYUIOP";

int demo_creat_main(void)
{
	int m_fd;
	// 创建文件
	m_fd = creat("myfile.txt", S_IRWXU | S_IRGRP | S_IROTH);
	if (m_fd < 0) {
		perror("creat error");
		exit(1);
	}
	if (write(m_fd, buf1, sizeof(buf1)) != sizeof(buf1)) {
		perror("write error");
	}
	if (lseek(m_fd, OFFSET, SEEK_SET) == -1) {
		perror("lseek error");
	}
	if (write(m_fd, buf2, sizeof(buf2)) != sizeof(buf2)) {
		perror("write error");
	}
	// 创建一个空洞文件，空洞文件是多线程的支持点之一，因为空洞文件的存在才能支持多线程断点续传

	exit(0);
}
