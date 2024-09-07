#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAMELEN 16
#define SLEEP 5

#define errExitEN(en, msg)          \
	do {                        \
		errno = en;         \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

static void *test_set_thread_name(void *parm)
{
	sleep(SLEEP); // allow main program to set the thread name
	return NULL;
}

int demo_setname_np_main(int argc, char **argv)
{
	pthread_t thread;
	int ret;
	char thread_name[NAMELEN];

	ret = pthread_create(&thread, NULL, test_set_thread_name, NULL);
	if (ret != 0) {
		errExitEN(ret, "pthread_create");
	}

	ret = pthread_getname_np(thread, thread_name, NAMELEN);
	if (ret != 0) {
		errExitEN(ret, "pthread_getname_np");
	}

	printf("Created a thread. Default name is: %s\n", thread_name);
	// 设置线程名
	ret = pthread_setname_np(thread, (argc > 1) ? argv[1] : "THREADFOO");
	if (ret != 0) {
		errExitEN(ret, "pthread_setname_np");
	}

	sleep(2);

	// 获取线程名
	ret = pthread_getname_np(thread, thread_name,
				 (argc > 2) ? atoi(argv[1]) : NAMELEN);
	if (ret != 0) {
		errExitEN(ret, "pthread_getname_np");
	}
	printf("The thread name after setting it is %s.\n", thread_name);

	ret = pthread_join(thread, NULL);
	if (ret != 0) {
		errExitEN(ret, "pthread_join");
	}

	printf("Done\n");
	exit(EXIT_SUCCESS);
}
