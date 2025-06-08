#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 256
int demo_pwrite_main(void)
{
	char pathname[] = "/tmp/myfile"; /*待操作文件路径*/
	int f_id; /*文件描述符*/

	off_t f_offset; /*文件指针偏移量*/

	ssize_t nwrite; /*实际写入的字节数*/
	char buf[BUFFSIZE] = "0123456789abcd"; /*待写入数据*/
	size_t nbytes; /*准备写入的字节数*/

	/*打开文件，获取文件标识符*/
	f_id = open(pathname, O_RDWR | O_CREAT);
	if (f_id == -1) {
		printf("open error for %s\n", pathname);
		return 1;
	}

	/*把文件指针移动到文件开始处*/
	f_offset = lseek(f_id, 0, SEEK_SET);
	if (f_offset == -1) {
		printf("lseek error for %s\n", pathname);
		return 2;
	}

	/*写入7个字节数据[0-6]*/
	nbytes = 7;
	nwrite = write(f_id, buf, nbytes);
	if (nwrite == -1) {
		printf("write error for %s\n", pathname);
		return 3;
	}

	/*=======调用pwrite从第一个字节后面写入四个字节数据[abcd]=======*/
	nbytes = 4;
	nwrite = pwrite(f_id, (buf + 10), nbytes, 1);
	if (nwrite == -1) {
		printf("pwrite error for %s\n", pathname);
		return 4;
	}

	/*再写入3个字节数据[7-9]*/
	nbytes = 3;
	nwrite = write(f_id, (buf + 7), nbytes);
	if (nwrite == -1) {
		printf("write error for %s\n", pathname);
		return 5;
	}

	/*关闭文件*/
	close(f_id);

	return EXIT_SUCCESS;
}
