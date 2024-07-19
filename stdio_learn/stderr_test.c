#include <stdio.h>
#include <stdlib.h>

int demo_stderr_main(int argc, char *argv[])
{
	fprintf(stderr, "11111111");
	fprintf(stdout, "22222222");
	return EXIT_SUCCESS;
}
