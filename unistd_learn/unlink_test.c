#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 删除文件(引用次数为零时)
int demo_unlink_main(int argc, char **argv)
{
	char *filename1 = "file1.txt";
	if (open(filename1, O_RDWR) < 0) {
		perror("open tempfile file faied");
		exit(EXIT_FAILURE);
	}
	if (unlink(filename1) < 0) {
		perror("unlink error");
		exit(EXIT_FAILURE);
	}
	printf("file unlinked \n");
	printf("done\n");
	exit(EXIT_SUCCESS);
}

// Output:
// ❯ xmake run unistd_learn unlink
// file unlinked
// done
// ❯ ls -alh build/linux/x86_64/debug/file1.txt
// "build/linux/x86_64/debug/file1.txt": No such file or directory (os error 2)
