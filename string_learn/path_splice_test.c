#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int path_splice(char *buf, int buf_len, const char *path, char *name)
{
	char *p = NULL;
	if (path == NULL || name == NULL) {
		return -1;
	}

	if (buf_len < strlen(path) + strlen(name) + 2) {
		return -2;
	}

	p = strcpy(buf, path);
	if (p[strlen(p) - 1] != '/') {
		strcat(p, "/");
	}
	strcat(p, name);
	return 0;
}

int demo_path_splice_main(int argc, char *argv[])
{
	char buf[1024];
	int ret;
	ret = path_splice(buf, sizeof(buf), "/home/black/", "test.txt");
	if (ret == 0) {
		printf("path_splice success: %s\n", buf);
	} else {
		printf("path_splice failed: %d\n", ret);
	}
	ret = path_splice(buf, sizeof(buf), "/home/black", "test.txt");
	if (ret == 0) {
		printf("path_splice success: %s\n", buf);
	} else {
		printf("path_splice failed: %d\n", ret);
	}
	return EXIT_SUCCESS;
}
