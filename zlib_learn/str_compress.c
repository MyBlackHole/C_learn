#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define NUM 1024

#define TMPPATH "/tmp/zlib_compress_test"

int demo_str_compress_main()
{
	/* 原始数据 */
	unsigned char str_src[] = "000000010000000000000014";
	unsigned char buf[NUM] = { 0 };
	unsigned char str_dst[NUM] = { 0 };
	unsigned long src_len = sizeof(str_src);
	unsigned long buf_len = sizeof(buf);
	unsigned long dst_len = sizeof(str_dst);
	int tmp_fd;
	size_t write_len = 0;

	printf("Src string:%s\nLength:%ld\n", str_src, src_len);

	/* 压缩 */
	compress(buf, &buf_len, str_src, src_len);
	printf("After Compressed Length:%ld\n", buf_len);

	tmp_fd = open(TMPPATH, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (tmp_fd <= 0) {
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("write Compressed string\n");
	write_len = write(tmp_fd, buf, buf_len);
	if (write_len != buf_len) {
		perror("write_len != buf_len");
		close(tmp_fd);
		exit(EXIT_FAILURE);
	}

	close(tmp_fd);

	/* 解压缩 */
	uncompress(str_dst, &dst_len, buf, buf_len);
	printf("After UnCompressed Length:%ld\n", dst_len);

	printf("UnCompressed String:%s\n", str_dst);

	return EXIT_SUCCESS;
}
