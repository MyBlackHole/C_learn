#include <stdio.h>
#include <stdlib.h>

int demo_fgetc_main(int argc, char *argv[])
{
	FILE *fp_tmp = NULL;
	int count = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(1);
	}

	fp_tmp = fopen(argv[1], "r");
	if (fp_tmp == NULL) {
		perror("fopen()");
		exit(1);
	}

	while (fgetc(fp_tmp) != EOF) {
		count++;
	}

	fprintf(stdout, "count %d\n", count);

	fclose(fp_tmp);

	exit(0);
}
