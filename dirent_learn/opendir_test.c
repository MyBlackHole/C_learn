#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int demo_opendir_test_main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dirp;

	if (argc != 2) {
		perror("usage: ls directory_name");
	}
	dir = opendir(argv[1]);
	if (dir == NULL) {
		fprintf(stderr, "can't open %s\n", argv[1]);
		fprintf(stderr, "err %s, id %d\n", strerror(errno), errno);
	}
	while ((dirp = readdir(dir)) != NULL) {
		fprintf(stderr, "%s\n", dirp->d_name);
	}

	closedir(dir);
	exit(0);
}
