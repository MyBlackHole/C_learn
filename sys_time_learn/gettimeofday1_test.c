#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int demo_gettimeofday1_main(void)
{
	int index;
	struct timeval tv_tmp;

	for (index = 0; index < 4; index++) {
		gettimeofday(&tv_tmp, NULL);
		printf("%ld\t%ld\n", tv_tmp.tv_usec, tv_tmp.tv_sec);
		sleep(1);
	}

	return 0;
}
