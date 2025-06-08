#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_getuid_main(void)
{
	printf("uid=%d  gid=%d  \n", getuid(), getgid());
	exit(EXIT_SUCCESS);
}
