#include <fcntl.h>
#include <stdio.h>

int demo_fileno1_main()
{
	FILE *fp_tmp;
	int fd_tmp = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd_tmp == -1) {
		fputs("file open error", stderr);
		return -1;
	}

	printf("First file descriptor : %d \n", fd_tmp);
	fp_tmp = fdopen(fd_tmp, "w"); // 转成 file 指针
	fputs("TCP/IP SOCKET PROGRAMMING \n", fp_tmp);
	printf("Second file descriptor: %d \n",
	       fileno(fp_tmp)); // 转回文件描述符
	fclose(fp_tmp);
	return 0;
}
