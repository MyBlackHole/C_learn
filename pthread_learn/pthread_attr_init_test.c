/* 举例验证 - 涉及线程的继承、调度、参数 */

#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>

void *child_thread(void *arg)
{
	int policy = 0;
	int max_priority = 0;
	int min_priority = 0;
	struct sched_param param;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_getinheritsched(&attr, &policy);
	if (policy == PTHREAD_EXPLICIT_SCHED) {
		printf("Inheritsched:PTHREAD_EXPLICIT_SCHED\n");
	}
	if (policy == PTHREAD_INHERIT_SCHED) {
		printf("Inheritsched:PTHREAD_INHERIT_SCHED\n");
	}

	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	pthread_attr_getschedpolicy(&attr, &policy);
	if (policy == SCHED_FIFO) {
		printf("Schedpolicy:SCHED_FIFO\n");
	}
	if (policy == SCHED_RR) {
		printf("Schedpolicy:SCHED_RR\n");
	}
	if (policy == SCHED_OTHER) {
		printf("Schedpolicy:SCHED_OTHER\n");
	}
	max_priority = sched_get_priority_max(policy);
	min_priority = sched_get_priority_min(policy);
	// 优先权
	printf("Maxpriority:%u\n", max_priority);
	printf("Minpriority:%u\n", min_priority);

	param.sched_priority = max_priority;
	pthread_attr_setschedparam(&attr, &param);
	// 调度优先权
	printf("sched_priority:%u\n", param.sched_priority);
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
}

int demo_attr_init_main(int argc, char *argv[])
{
	pthread_t child_thread_id;
	pthread_create(&child_thread_id, NULL, child_thread, NULL);
	pthread_join(child_thread_id, NULL);

	return 0;
}
