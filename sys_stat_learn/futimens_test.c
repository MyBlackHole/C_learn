#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int demo_futimens_main(int argc, char **argv)
{
	int i, fd;
	struct stat buf;
	struct timespec times[2];
	for (i = 1; i < argc; i++) {
		if (stat(argv[i], &buf) < 0) // fetch the current time
		{
			fprintf(stderr, "%s:stat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
			fprintf(stderr, "%s:open error ", argv[i]);
			continue;
		}
		times[0] = buf.st_atim;
		times[1] = buf.st_mtim;

		// 修改文件信息
		if (futimens(fd, times) < 0) { // reset times
			fprintf(stderr, "%s:futimes error", argv[i]);
		}
		close(fd);
	}
	exit(0);
}
