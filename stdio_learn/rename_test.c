#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int demo_rename_main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s old_name new_name\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (rename(argv[1], argv[2]) == -1) {
		perror("rename");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
