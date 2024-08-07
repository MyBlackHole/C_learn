#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_dup22_main(int argc, char *argv[])
{
	int cfd1;
	int cfd2;
	char str1[] = "Hi~ \n";
	char str2[] = "It's nice day~ \n";

	// 复制文件描述符 1, 等效与 fcntl(oldfd, F_DUPFD, 1)
	cfd1 = dup(1);

	// 再次复制文件描述符,定为数值 7
	// 7 重定向到 cfd1,
	// fcntl(cfd1, F_DUPFD, 7);
	// close(cfd1);
	cfd2 = dup2(cfd1, 7);

	printf("fd1=%d , fd2=%d \n", cfd1, cfd2);
	write(cfd1, str1, sizeof(str1));
	write(cfd2, str2, sizeof(str2));

	close(cfd1);
	close(cfd2); // 终止复制的文件描述符，但是仍有一个文件描述符
	write(1, str1, sizeof(str1));
	close(1);
	write(1, str2, sizeof(str2)); // 无法完成输出
	return EXIT_SUCCESS;
}
