#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_getpid_main(int argc, char **argv)
{
	printf("getpid_test.c from process Id %ld\n", (long)getpid());
	exit(EXIT_SUCCESS);
}
