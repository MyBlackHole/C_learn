#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_fopen_main(int argc, char *argv[])
{
	FILE *fp_tmp = NULL;
	fp_tmp = fopen("/tmp/stdio_tmp", "r");
	if (fp_tmp == NULL) {
		// fprintf(stderr, "fopen() failed!  errno = %d\n", errno);
		perror("fopen()");
		// fprintf(stderr, "fopen() failed!  errno = %s\n", strerror(errno));
		exit(1);
	}

	puts("OK");

	fclose(fp_tmp);
	exit(0);
}
