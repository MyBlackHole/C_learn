#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

int demo_read1_main(int argc, char *argv[])
{
	int fd_dest = 0;
	/*char buf[512];*/
	char buf[BUFSIZE];
	unsigned int len = 0;
	int count = 0;
	printf("demo_read_main()\n");

	sleep(100);
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <dest_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Destination file: %s\n", argv[2]);
	fd_dest = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_dest < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	printf("Copying data from %s to %s\n", argv[1], argv[2]);
	count = 5;
	while (true) {
		if (count == 0)
		{
			// 测试异常退出
			printf("count == 0, exit(EXIT_FAILURE)\n");
			exit(EXIT_FAILURE);
		}
		len = read(STDIN_FILENO, buf, BUFSIZE);
		if (len < 0) {
			perror("read()");
			close(fd_dest);
			exit(EXIT_FAILURE);
		}
		if (len == 0) {
			printf("Reached end of %s\n", argv[1]);
			break;
		}
		printf("Read %d bytes from %s\n", len, argv[1]);
		write(fd_dest, buf, len);
		count--;
		sleep(1);
	}

	close(fd_dest);

	printf("demo_read_main() done.\n");
	exit(EXIT_SUCCESS);
}

/*output:*/
/*❯ cat /tmp/preamble-2d8b3f.pch | xmake run unistd_learn read1 /tmp/test1*/
/*demo_read_main()*/
/*Destination file: (null)*/
/*Copying data from /tmp/test1 to (null)*/
/*Read 1024 bytes from /tmp/test1*/
/*Read 1024 bytes from /tmp/test1*/
/*Read 1024 bytes from /tmp/test1*/
/*Read 1024 bytes from /tmp/test1*/
/*Read 1024 bytes from /tmp/test1*/
/*count == 0, exit(EXIT_FAILURE)*/
/*error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/unistd_learn read1 /tmp/test1) failed(1)*/
