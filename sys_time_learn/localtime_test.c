#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int demo_localtime_main(void)
{
	time_t t_tmp;
	struct tm *mytime;
	char buf[16];
	char buff[64];
	time(&t_tmp);
	mytime = localtime(&t_tmp);
	if (strftime(buf, 16, "time and date : %r ,%a %b %d, %Y", mytime) ==
	    0) {
		printf("bufer length is too small\n");
	} else {
		printf("%s\n", buf);
	}
	if (strftime(buff, 64, "time and date : %r ,%a %b %d, %Y", mytime) ==
	    0) {
		printf("bufer length is too small\n");
	} else {
		printf("%s\n", buff);
	}
	exit(0);
}
