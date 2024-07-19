#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char dpath[PATH_MAX];
	char *dir;
	if (argc != 2) {
		perror("exec dir");
		return EXIT_FAILURE;
	}

	dir = argv[1];

	// 获取真实路径
	if (dir && !realpath(dir, dpath)) {
		return EXIT_FAILURE;
	}

	printf("%s\n", dpath);

	return EXIT_SUCCESS;
}
