#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int demo_link_main()
{
	int fd1, fd2;
	char *filename1 = "file1.txt";
	char *filename2 = "file2.txt";

	fd1 = open(filename1, O_CREAT | O_WRONLY, 0644);
	if (fd1 == -1) {
		perror("open");
		return 1;
	}

	write(fd1, "Hello, world!", 13);
	sync();

	// 硬链接 file1.txt 到 file2.txt
	fd2 = link(filename1, filename2);
	if (fd2 == -1) {
		perror("link");
		return 1;
	}
	printf("File %s has been linked to %s.\n", filename1, filename2);
	close(fd1);
	close(fd2);
	return 0;
}

// Output:
// ❯ ls -alh build/linux/x86_64/debug/file1.txt build/linux/x86_64/debug/file2.txt
// Permissions Size User  Date Modified Name
// .rw-r--r--    13 black 31 Jul 14:43   build/linux/x86_64/debug/file1.txt
//
// ❯ xmake run unistd_learn link
// File file1.txt has been linked to file2.txt.
// ❯ ls -alh build/linux/x86_64/debug/file1.txt build/linux/x86_64/debug/file2.txt
// Permissions Size User  Date Modified Name
// .rw-r--r--    13 black 31 Jul 14:43   build/linux/x86_64/debug/file1.txt
// .rw-r--r--    13 black 31 Jul 14:43   build/linux/x86_64/debug/file2.txt
