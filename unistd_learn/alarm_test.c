#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECONDS 5

void handler()
{
	// 会死锁
	// stdout 持有锁
	printf("hello\n");
}

int demo_alarm_main()
{
	int index;
	signal(SIGALRM, handler);
	alarm(SECONDS);
	for (index = 1; index < 7; index++) {
		printf("sleep %d ...\n", index);
		sleep(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
