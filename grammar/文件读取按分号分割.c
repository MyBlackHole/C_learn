#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int demo_read_file_by_semicolon_main()
{
	int ret = 0;
	int fd = -1;
	int read_len = 0;
	int i, j = 0;
	char buf[PATH_MAX + 1] = { 0 };
	char line[PATH_MAX] = { 0 };
	char *download_files_path = "/tmp/4.txt";

	if (download_files_path == NULL || download_files_path[0] == '\0') {
		ret = -1;
		goto return__;
	}

	fd = open(download_files_path, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open file [%s] failure: %s(errno: %d)\n",
			download_files_path, strerror(errno), errno);
		ret = -1;
		goto return__;
	}

	while (true) {
		read_len = read(fd, buf, PATH_MAX + 1);
		if (read_len <= 0) {
			break;
		}
		buf[read_len] = '\0';
		for (i = 0; buf[i]; i++) {
			if (buf[i] != ';') {
				line[j] = buf[i];
				j++;
			} else if (buf[i] == ';') {
				printf("%s\n", line);
				memset(line, 0, sizeof(line));
				j = 0;
			}
		}
		memset(buf, 0, sizeof(buf));
	}
	if (strlen(line) > 1) {
		printf("[%s], len: %ld\n", line, strlen(line));
	}
	printf("ok\n");

	ret = 0;
	close(fd);

return__:
	return ret;
}
