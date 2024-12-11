#include <stdio.h>
#include <stdlib.h>

int demo_sprintf_main(int argc, char *argv[])
{
	char buf[1024];
	int year = 2014;
	int month = 5;
	int day = 13;
	sprintf(buf, "%d-%d-%d", year, month, day);
	puts(buf);
	sprintf(buf, "%d-%d-%d", year, month, day);
	puts(buf);
	exit(EXIT_SUCCESS);
}
