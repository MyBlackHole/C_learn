#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int demo_mkdir_main(int argc, char *argv[])
{
	int rv;
	char *path = dirname(argv[0]);
	char *filename = "/dir";
	char *name = malloc(strlen(path) + strlen(filename));

	strcpy(name, path);
	strcat(name, filename);

	rv = mkdir(name, S_IRWXU);
	if (rv != 0) {
		printf("error: create directory '%s': %s", name,
		       strerror(errno));
		return 1;
	}
	return 0;
}
