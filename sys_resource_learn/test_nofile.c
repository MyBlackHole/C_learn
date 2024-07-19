#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <errno.h>

int demo_test_nofile_main()
{
	struct rlimit nofile = { 0 };

	if (getrlimit(RLIMIT_NOFILE, &nofile) < 0) {
		perror("unable to query NOFILE limit:");
		return EXIT_FAILURE;
	}

	nofile.rlim_cur = 10;

	if (setrlimit(RLIMIT_NOFILE, &nofile) == -1) {
		perror("setrlimit");
		return EXIT_FAILURE;
	}

	printf("Current limit: %lu\n", nofile.rlim_cur);

	// 测试打开文件数量是否受到限制
	FILE *fp;
	int count = 0;
	for (int i = 0; i < 10; i++) {
		fp = fopen("test.txt", "w");
		if (fp == NULL) {
			perror("fopen");
			printf("errno: %d\n", errno);
			return EXIT_FAILURE;
		}
		printf("File opened: %d\n", i);
		count++;
	}
	// fclose(fp);

	printf("File opened successfully.\n");
	return EXIT_SUCCESS;
}

// out:
// ❯ xmake run sys_resource_learn test_nofile
// Current limit: 10
// File opened: 0
// File opened: 1
// File opened: 2
// File opened: 3
// fopen: Too many open files
// errno: 24
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/sys_resource_learn test_nofile) failed(1)
