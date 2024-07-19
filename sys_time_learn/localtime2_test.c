#include <stdio.h>
#include <time.h>

#define TIMESTRSIZE 1024

int demo_localtime2_main(int argc, char *argv[])
{
	time_t stamp;
	struct tm *tm_tmp;
	char timestr[TIMESTRSIZE];

	stamp = time(NULL);
	printf("%ld\n", stamp);
	tm_tmp = localtime(&stamp);
	strftime(timestr, TIMESTRSIZE, "NOW:%Y-%m-%d", tm_tmp);
	puts(timestr);

	tm_tmp->tm_mday += 100;
	// 处理溢出
	mktime(tm_tmp);
	strftime(timestr, TIMESTRSIZE, "100 days later:%Y-%m-%d", tm_tmp);
	puts(timestr);

	return 0;
}

// xmake run sys_time_learn localtime2
