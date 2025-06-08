#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	time_t time_value;
	struct tm *tmp;
	char buf1[16];
	char buf2[64];

	time(&time_value);
	tmp = localtime(&time_value);
	if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0) {
		printf("buffer length 16 is too small\n");
	} else {
		printf("%s\n", buf1);
	}
	if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0) {
		printf("buffer length 64 is too small\n");
	} else {
		printf("%s\n", buf2);
	}
	exit(EXIT_FAILURE);
}
