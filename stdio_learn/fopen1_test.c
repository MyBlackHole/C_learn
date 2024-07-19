#include <stdio.h>
#include <stdlib.h>

int demo_fopen1_main(int argc, char *argv[])
{
	FILE *fps = NULL;
	FILE *fpd = NULL;
	int item;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <src_file> <dest_file>\n", argv[0]);
		exit(1);
	}

	fps = fopen(argv[1], "r");
	if (fps == NULL) {
		perror("fopen()");
		exit(1);
	}

	fpd = fopen(argv[2], "w");
	if (fpd == NULL) {
		fclose(fps);
		perror("fopen()");
		exit(1);
	}

	while (1) {
		item = fgetc(fps);
		if (item == EOF) {
			break;
		}
		fputc(item, fpd);
	}

	fclose(fpd);
	fclose(fps);

	exit(0);
}
