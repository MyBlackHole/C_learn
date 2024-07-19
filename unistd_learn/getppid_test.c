#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_getppid_main(int argc, char **argv)
{
	printf("getppid_test.c from process Id %ld\n", (long)getppid());
	exit(EXIT_SUCCESS);
}
