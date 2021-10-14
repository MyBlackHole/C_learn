#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	printf("uid=%d  gid=%d  \n",getuid(),getgid());
	exit(0);

}
