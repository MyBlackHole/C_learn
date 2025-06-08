#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
// #include <unistd.h>
#include <signal.h>

int demo_sigemptyset_main(int argc, char *argv[])
{
	sigset_t set;
	// 清除SET中的所有信号
	sigemptyset(&set);
	printf("set: %lu\n", set.__val[0]);
	return EXIT_SUCCESS;
}
