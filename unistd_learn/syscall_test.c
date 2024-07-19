#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int demo_syscall_main()
{
	int ret;
	ret = syscall(SYS_chmod, "/etc/passwd", 0444);

	if (ret == -1) {
		fprintf(stderr, "chmod failed, errno = %d\n", errno);
	} else {
		printf("chmod succeess!\n");
	}
	return EXIT_SUCCESS;
}
