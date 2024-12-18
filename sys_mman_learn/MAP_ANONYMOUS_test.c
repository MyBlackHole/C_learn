#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int var = 12;

int demo_MAP_ANONYMOUS_main(int argc, char *argv[])
{
	int *mf;
	pid_t pid;
	// MAP_ANONYMOUS == MAP_ANON
	mf = (int *)mmap(NULL, 4, PROT_READ | PROT_WRITE,
			 MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (mf == MAP_FAILED) {
		perror("mmap error.");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0) {
		perror("fork error.");
		munmap(mf, 4);
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		*mf = 100;
		var = 24;
		printf("child: *mf = %d;var = %d\n", *mf, var);
	} else {
		sleep(1);
		printf("parent: *mf = %d;var = %d\n", *mf, var);
		wait(NULL);

		munmap(mf, 4);
	}

	return EXIT_SUCCESS;
}

// output:
// 
// child: *mf = 100;var = 24
// parent: *mf = 100;var = 12
