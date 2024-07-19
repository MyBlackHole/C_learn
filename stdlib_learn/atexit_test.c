#include <stdio.h>
#include <stdlib.h>

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
	if (atexit(my_exit2) != 0) {
		perror("can't register my_exit2)");
		exit(1);
	}
	if (atexit(my_exit1) != 0) {
		perror("can't register my_exit1");
		exit(1);
	}
	if (atexit(my_exit1) != 0) {
		perror("can't register my_exit1");
		exit(1);
	}
	printf("main is done \n");
	return 0;
}

static void my_exit1(void)
{
	printf("first exit hander\n");
}
static void my_exit2(void)
{
	printf("second exit hander\n");
}
