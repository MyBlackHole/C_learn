#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif
#include <sys/sysmacros.h>

int demo_stat3_main(int argc, char **argv)
{
	int i;
	struct stat buf;
	for (i = 1; i < argc; i++) {
		printf("%s:\n", argv[i]);
		if (stat(argv[i], &buf) < 0) {
			perror("stat error");

			continue;
		}

		// major minor 主次设备号
		printf("dev=%d:%d", major(buf.st_dev), minor(buf.st_dev));
		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
			printf("(%s)rdev=%d%d",
			       (S_ISCHR(buf.st_mode)) ? "cahracter " : "block",
			       major(buf.st_rdev), minor(buf.st_rdev));
		}
		printf("\n");
	}
	exit(0);
}
