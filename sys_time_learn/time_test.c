#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int demo_time_main()
{
	time_t t_tmp = time((time_t *)NULL);
	printf("start time: %lu", t_tmp);
	return EXIT_SUCCESS;
}
