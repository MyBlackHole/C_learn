#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int demo_readdir_test_main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *dirp;

	if (argc < 2) {
		fprintf(stderr, "usage:ls directory_name");
		exit(1);
	}
	dir = opendir(argv[1]);
	if (dir == NULL) {
		fprintf(stderr, "can't open %s", argv[1]);
	}
	while ((dirp = readdir(dir)) != NULL) {
		printf("%s\n", dirp->d_name);
	}
	closedir(dir);
	exit(EXIT_SUCCESS);
}
