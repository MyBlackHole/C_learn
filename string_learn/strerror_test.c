#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_strerror_test_main(int argc, char *argv[])
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}
