#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int demo_sleep_main()
{
	time_t time1 = time((time_t *)NULL);
	printf("start time: %lu\n", time1);
	fflush(stdout);
	sleep(4);
	time_t time2 = time((time_t *)NULL);
	printf("start time: %lu\n", time2);
	return EXIT_SUCCESS;
}
