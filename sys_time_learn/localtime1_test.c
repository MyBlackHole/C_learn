#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME "/tmp/out"

#define BUFSIZE 1024

int demo_localtime1_main()
{
	FILE *fp_tmp = NULL;
	char buf[BUFSIZE];
	int count = 0;
	time_t stamp;
	struct tm *tm_tmp = NULL;

	fp_tmp = fopen(FNAME, "a+");
	if (fp_tmp == NULL) {
		perror("fopen erron");
		exit(1);
	}

	while (fgets(buf, BUFSIZE, fp_tmp) != NULL) {
		count++;
	}

	while (1) {
		time(&stamp);
		tm_tmp = localtime(&stamp);
		fprintf(fp_tmp, "%d----%d-%d-%d %d:%d:%d\n", ++count,
			tm_tmp->tm_year + 1900, tm_tmp->tm_mon + 1,
			tm_tmp->tm_mday, tm_tmp->tm_hour, tm_tmp->tm_min,
			tm_tmp->tm_sec);
		fflush(fp_tmp);
		sleep(1);
	}

	fclose(fp_tmp);

	exit(0);
}
