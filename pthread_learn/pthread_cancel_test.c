#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void *my_pthread_function1(void *arg)
{
	int i = 0;

	while (1) {
		printf("thread function, i: %d\n", i++);
		sleep(1);
	}
	return NULL;
}

static void *my_pthread_function2(void *arg)
{
	/*int i = 0;*/

	while (1) {
	}
	return NULL;
}

int demo_pthread_cancel_main()
{
	pthread_t tid;
	pid_t pid;

	pid = getpid();

	printf("pid: %d\n", pid);
	pthread_create(&tid, NULL, my_pthread_function1, NULL);
	(void)my_pthread_function2;

	// 将线程分离, 为了可以自动释放资源
	// 不然需要 pthread_join 等待线程结束后才能释放资源
	pthread_detach(tid);

	sleep(10);
	pthread_cancel(tid);
	printf("had cancel the thread!\n");
	sleep(10);

	return EXIT_SUCCESS;
}

// pthread_cancel
// pthread_cancel 函数用来终止一个线程。
// 调用 pthread_cancel 函数后，线程会处于 PTHREAD_CANCEL_ENABLE 状态。
// 待线程进入内核空间后才会被真正的终止。
// 所以线程一直运行在用户空间，不会被真正的终止。
//
// OUTPUT: (my_pthread_function1)
// xmake run pthread_learn pthread_cancel
// thread function, i: 0
// thread function, i: 1
// thread function, i: 2
// thread function, i: 3
// thread function, i: 4
// had cancel the thread!
//
//
// ps -T -p 35470
//   PID    SPID TTY          TIME CMD
// 35470   35470 pts/5    00:00:00 pthread_learn
// 35470   35472 pts/5    00:00:00 pthread_learn
// ps -T -p 35470
//   PID    SPID TTY          TIME CMD
// 35470   35470 pts/5    00:00:00 pthread_learn
//
//
// OUTPUT: (my_pthread_function2)
// ❯ xmake run pthread_learn pthread_cancel
// pid: 34976
// had cancel the thread!
//
// ps -T -p 34976
//   PID    SPID TTY          TIME CMD
// 34976   34976 pts/5    00:00:00 pthread_learn
// 34976   34978 pts/5    00:00:18 pthread_learn
