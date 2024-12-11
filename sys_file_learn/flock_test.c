#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int demo_flock_main()
{
	char path[] = "file.txt";
	int my_fd = 0;
	int count = 0;

	my_fd = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (my_fd < 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// 堵塞获取
	if (flock(my_fd, LOCK_EX) == 0) {
	/*if (flock(my_fd, LOCK_EX | LOCK_NB) == 0) {*/
		printf("the file was locked.\n");
	} else {
		printf("the file was not locked.\n");
	}
	/*close(my_fd);*/

	while (1) {
		sleep(1);
		if (count == 10) {
			break;
		} else {
			count++;
		}
	}

	close(my_fd);

	return EXIT_SUCCESS;
}
