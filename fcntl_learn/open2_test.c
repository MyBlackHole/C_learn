#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

int demo_open2_main(int argc, char *argv[])
{
	int sfd = 0;
	int dfd = 0;
	/*char buf[BUFSIZE] = { 0 };*/
	/*size_t len = 0;*/
	/*size_t ret = 0;*/
	/*int pos = 0;*/

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <desc_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	dfd = open(argv[1], O_RDONLY);
	if (sfd < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	getc(stdin);

	close(dfd);
	close(sfd);

	exit(EXIT_SUCCESS);
}
