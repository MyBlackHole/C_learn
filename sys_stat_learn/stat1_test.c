#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static int ftype(const char *fname)
{
	struct stat statres;
	if (stat(fname, &statres) < 0) {
		perror("stat()");
		exit(1);
	}

	if (S_ISREG(statres.st_mode)) {
		return '-';
	} else if (S_ISDIR(statres.st_mode)) {
		return 'd';
	} else if (S_ISSOCK(statres.st_mode)) {
		return 's';
	} else if (S_ISLNK(statres.st_mode)) {
		return 'l';
	} else {
		return '?';
	}
}

int demo_stat1_main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "<path>");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "%c\n", ftype(argv[1]));

	exit(0);
}
