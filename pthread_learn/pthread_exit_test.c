#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_exit(int err, char *s)
{
	perror(strerror(err));
	exit(1);
}

void *thr_fn_1(void *arg)
{
	printf("thread 1 returning\n");
	return ((void *)1);
}

void *thr_fn_2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_exit((void *)2);
}

int demo_exit_main(void)
{
	int err;
	pthread_t tid1;
	pthread_t tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn_1, NULL);
	if (err != 0) {
		err_exit(err, "can't create thread 1");
	}
	err = pthread_create(&tid2, NULL, thr_fn_2, NULL);
	if (err != 0) {
		err_exit(err, "can't create thread 2");
	}
	err = pthread_join(tid1, &tret);
	if (err != 0) {
		err_exit(err, "can't join with thread 1");
	}
	printf("thread 1 exit code %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0) {
		err_exit(err, "can't join with thread 2");
	}
	printf("thread 2 exit code %ld\n", (long)tret);
	exit(0);
}
