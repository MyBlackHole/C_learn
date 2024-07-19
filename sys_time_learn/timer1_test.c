/**
 * @file 3.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/18 22:10:26
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void timer(int sig)
{
	if (SIGALRM == sig) {
		printf("timer\n");
		alarm(2);
	}

	return;
}

int demo_timer1_main()
{
	signal(SIGALRM, timer);
	alarm(1);
	getchar();
	return 0;
}
