#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int demo_timespec_main(int argc, char *argv[])
{
	struct timespec now;
	timespec_get(&now, TIME_UTC);
	char buff[64];
	strftime(buff, sizeof(buff), "%D %T", gmtime(&now.tv_sec));
	printf("time:%s.%09ld UTC\n", buff, now.tv_nsec);
	return 0;
}
