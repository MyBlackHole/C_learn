#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_getline_main(int argc, char *argv[])
{
	FILE *fp_tmp = NULL;
	char *linebuf = NULL;
	size_t linesize = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(1);
	}

	fp_tmp = fopen(argv[1], "r");
	if (fp_tmp == NULL) {
		perror("fopen()");
		exit(1);
	}

	while (1) {
		// 会连同换行一起读入
		if (getline(&linebuf, &linesize, fp_tmp) < 0) {
			break;
		}
		fprintf(stdout, "%lu\n", strlen(linebuf));
		fprintf(stdout, "%lu\n", linesize);
	}
	free(linebuf);

	fclose(fp_tmp);

	exit(0);
}
