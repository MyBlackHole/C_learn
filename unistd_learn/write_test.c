#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 4096

int demo_write_main(void)
{
	size_t num;
	char buf[BUFFSIZE];

	while ((num = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if (write(STDOUT_FILENO, buf, num) != num) {
			perror("write error");
			exit(EXIT_FAILURE);
		}
	}

	if (num < 0) {
		perror("read error");
	}

	exit(EXIT_SUCCESS);
}
