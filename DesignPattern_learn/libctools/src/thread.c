#include "thread.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "log.h"

#ifdef __APPLE__
static void *thread_run(void *data)
{
	Thread *thread = data;
	// pthread_setname_np(thread->name);
	thread->retval = thread->func(thread->data);
	return NULL;
}
#else
#include <sys/syscall.h>
static void *thread_run(void *data)
{
	Thread *thread = data;
	//    log_info("thread_run: [%d] %s", syscall(__NR_getthreadid),
	//    thread->name);
	// pthread_setname_np(pthread_self(), thread->name);
	thread->retval = thread->func(thread->data);
#ifdef __ANDROID__
//    SDL_JNI_DetachThreadEnv();
#endif
	return NULL;
}
#endif

Thread *thread_create(Thread *thread, int (*fn)(void *), void *data,
		      const char *name)
{
	if (name == NULL) {
		perror("check name\n");
		exit(EXIT_FAILURE);
	}
	thread->func = fn;
	thread->data = data;
	if (strlen(name) >= THREAD_FILE_NAME_LENGTH) {
		perror("name too long\n");
		exit(EXIT_FAILURE);
	}
	strncpy(thread->name, name, THREAD_FILE_NAME_LENGTH);
	int retval = pthread_create(&thread->id, NULL, thread_run, thread);
	if (retval) {
		return NULL;
	}

	return thread;
}

// 设置线程优先级
int thread_set_priority(ThreadPriority priority)
{
	struct sched_param sched;
	int policy;
	pthread_t thread = pthread_self();

	if (pthread_getschedparam(thread, &policy, &sched) < 0) {
		log_error("pthread_getschedparam() failed");
		return -1;
	}
	if (priority == THREAD_PRIORITY_LOW) {
		sched.sched_priority = sched_get_priority_min(policy);
	} else if (priority == THREAD_PRIORITY_HIGH) {
		sched.sched_priority = sched_get_priority_max(policy);
	} else {
		int min_priority = sched_get_priority_min(policy);
		int max_priority = sched_get_priority_max(policy);
		sched.sched_priority =
			(min_priority + (max_priority - min_priority) / 2);
	}
	if (pthread_setschedparam(thread, policy, &sched) < 0) {
		log_error("pthread_setschedparam() failed");
		return -1;
	}
	return 0;
}

pthread_t thread_get_pthread_id(Thread *thread)
{
	assert(thread);
	return thread->id;
}

void thread_wait(Thread *thread, int *status)
{
	assert(thread);
	if (!thread) {
		return;
	}

	pthread_join(thread->id, NULL);

	if (status) {
		*status = thread->retval;
	}
}

void thread_detach(Thread *thread)
{
	assert(thread);
	if (!thread) {
		return;
	}

	pthread_detach(thread->id);
}
