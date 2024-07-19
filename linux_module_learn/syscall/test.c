#include <stdio.h>
#include <syscall.h>
// #include <linux/unistd.h>
// #include <sys/types.h>
// #include <stdlib.h>

int main(void)
{
	printf("%d\n", syscall(335));
	return 0;
}
