#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define __DEBUG(x...)                                             \
	do {                                                      \
		fprintf(stderr, "[%d]	%s(%d)	", (int)getpid(), \
			__FUNCTION__, __LINE__);                  \
		fprintf(stderr, ##x);                             \
		fprintf(stderr, "\n");                            \
	} while (0)

#define PI 3.14
#define ADD (2 + 3)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char *argv[])
{
#define MAXINT 200
	printf("MAXINT = %d\n", MAXINT);
#undef MAXINT

	int MAXINT = 10;
	printf("MAXINT = %d\n", MAXINT);

	__DEBUG("%s", "blackhole");
	printf("%d\n", ADD * ADD);
	printf("%d\n", MAX(1, 2));
	exit(0);
}

/******** 例程1：main.c ********/
