#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

long uclock()
{
	struct timeval tv = { 0 };
	if (gettimeofday(&tv, NULL))
		return -1;
	return ((long)tv.tv_sec * 1000000 + tv.tv_usec);
}

int demo_gettimeofday3_main(int argc, char *argv[])
{
	printf("%ld\n", uclock());
	return EXIT_SUCCESS;
}
