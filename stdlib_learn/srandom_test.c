#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	srandom(1);
	printf("%ld\n", random());
	srandom(1);
	printf("%ld\n", random());
	srandom(time(NULL));
	printf("%ld\n", random());
	printf("%ld\n", random());
	return 0;
}
