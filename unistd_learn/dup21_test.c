#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int demo_dup21_main()
{
	int oldfd;
	int newfd;
	size_t len;
	char *buf = "This is a test!!!!\n";
	oldfd = open("dup21_STDOUT_test.txt", O_RDWR | O_CREAT | O_TRUNC,
		     S_IWUSR | S_IRUSR);
	if (oldfd < 0) {
		printf("open error\n");
		exit(EXIT_FAILURE);
	}
	newfd = dup2(oldfd, STDOUT_FILENO);
	/*newfd = dup2(oldfd, fileno(stdout));*/
	if (newfd < 0) {
		printf("dup2 error\n");
		exit(EXIT_FAILURE);
	}
	printf("dup2的返回值：%d\n", newfd);
	// 刷新缓冲区，使输出立即显示
	fflush(stdout);

	len = strlen(buf);
	// 本应该写入到stdout的信息，但是标准输出已经重定向到目标文件中，故向标准输出写的数据将会写到目标文件中。
	if (write(STDOUT_FILENO, buf, len) != len) {
		printf("write error!\n");
		exit(EXIT_FAILURE);
	}
	/*sleep(20);*/
	close(oldfd);
	/*// 这个不用关闭，因为它会自动关闭(STDOUT_FILENO)，不需要手动关闭*/
	/*close(newfd);*/
	exit(EXIT_SUCCESS);
}

// output:
// ❯ ls -alh /proc/766994/fd
// Permissions Size User  Date Modified Name
// lrwx------     - black 21 Sep 12:07   0 -> /dev/pts/2
// lrwx------     - black 21 Sep 12:07   1 -> /run/media/black/Data/Documents/c/build/linux/x86_64/debug/dup21_STDOUT_test.txt
// lrwx------     - black 21 Sep 12:07   2 -> /dev/pts/2
// lrwx------     - black 21 Sep 12:07   3 -> anon_inode:[eventpoll]
// lrwx------     - black 21 Sep 12:07   4 -> socket:[5130628]
// lrwx------     - black 21 Sep 12:07   5 -> socket:[5130629]
// lrwx------     - black 21 Sep 12:07   6 -> /run/media/black/Data/Documents/c/build/linux/x86_64/debug/dup21_STDOUT_test.txt
