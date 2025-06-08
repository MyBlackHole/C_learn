#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static int flen(char *fname)
{
	struct stat statres;
	if (stat(fname, &statres) < 0) {
		perror("stat()");
		exit(1);
	}
	return statres.st_size;
}

int demo_stat_main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "<path>");
		exit(1);
	}
	// char *path = "/tmp/tmp1";
	fprintf(stdout, "%d\n", flen(argv[1]));
	exit(0);
}

// output:
// ❯ xmake run sys_stat_learn stat /run/
// 600
// ❯ xmake run sys_stat_learn stat /run/sshd.pid
// 4
// ❯ xmake run sys_stat_learn stat /run/media/black/Data/Documents
// 0
// ❯ xmake run sys_stat_learn stat /run/media/black/Data/Documents/c/README.md
// 340
