#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

void *start_routine(void *arg)
{
	int i, j;

	while (1) {
		fprintf(stderr, "%c ", *(char *)arg);
		for (i = 0; i < 100000; i++)
			for (j = 0; j < 1000; j++)
				;
	}

	pthread_exit(NULL);
}

int demo_pthread_attr_setinheritsched_main(void)
{
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr1, attr2;
	struct sched_param param1, param2;

	/* 线程属性变量的初始化 */
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	/* 设置线程是否继承创建者的调度策略 PTHREAD_EXPLICIT_SCHED：不继承才能设置线程的调度策略*/
	errno = pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	if (errno != 0) {
		perror("setinherit failed\n");
		return -1;
	}

	/* 设置线程是否继承创建者的调度策略 PTHREAD_EXPLICIT_SCHED：不继承才能设置线程的调度策略*/
	errno = pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
	if (errno != 0) {
		perror("setinherit failed\n");
		return -1;
	}

	/* 设置线程的调度策略：SCHED_FIFO：抢占性调度; SCHED_RR：轮寻式调度；SCHED_OTHER：非实时线程调度策略*/
	errno = pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
	if (errno != 0) {
		perror("setpolicy failed\n");
		return -1;
	}

	errno = pthread_attr_setschedpolicy(&attr2, SCHED_RR);
	if (errno != 0) {
		perror("setpolicy failed\n");
		return -1;
	}

	//设置优先级的级别
	param1.sched_priority = 99;
	param2.sched_priority = 1;

	//查看抢占性调度策略的最小跟最大静态优先级的值是多少
	printf("min=%d, max=%d\n", sched_get_priority_min(SCHED_FIFO),
	       sched_get_priority_max(SCHED_FIFO));

	/* 设置线程静态优先级 */
	errno = pthread_attr_setschedparam(&attr1, &param1);
	if (errno != 0) {
		perror("setparam failed\n");
		return -1;
	}

	errno = pthread_attr_setschedparam(&attr2, &param2);
	if (errno != 0) {
		perror("setparam failed\n");
		return -1;
	}

	/* 创建三个测试线程 */
	/* 线程1，优先级1 */
	errno = pthread_create(&tid1, &attr1, start_routine, (void *)"1");
	if (errno != 0) {
		perror("create thread 1 failed\n");
		return -1;
	}
	/* 线程2，优先级1 */
	errno = pthread_create(&tid2, &attr2, start_routine, (void *)"2");
	if (errno != 0) {
		perror("create thread 2 failed\n");
		return -1;
	}
	/* 线程3，非实时线程，静态优先级0 */
	errno = pthread_create(&tid3, NULL, start_routine, (void *)"3");
	if (errno != 0) {
		perror("create thread 3 failed\n");
		return -1;
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	pthread_attr_destroy(&attr1);
	pthread_attr_destroy(&attr2);

	return EXIT_SUCCESS;
}
