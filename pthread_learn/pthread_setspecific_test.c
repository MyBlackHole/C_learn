/* CELEBP51 */
#include <stdint.h>
#include <stdint.h>
#define _OPEN_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define threads 3
#define BUFFSZ 48
pthread_key_t key;

void *threadfunc(void *parm)
{
	int status;
	void *value;
	int threadnum;
	int *tnum;
	void *getvalue;
	char Buffer[BUFFSZ];

	tnum = parm;
	threadnum = *tnum;

	printf("Thread %d executing\n", threadnum);

	if (!(value = malloc(sizeof(Buffer))))
		printf("Thread %d could not allocate storage, errno = %d\n",
		       threadnum, errno);
	status = pthread_setspecific(key, (void *)value);
	if (status < 0) {
		printf("pthread_setspecific failed, thread %d, errno %d",
		       threadnum, errno);
		pthread_exit((void *)12);
	}
	printf("Thread %d setspecific value: %d\n", threadnum,
	       (unsigned int)(uintptr_t)value);

	getvalue = pthread_getspecific(key);
	if (getvalue < 0) {
		printf("pthread_getspecific failed, thread %d, errno %d",
		       threadnum, errno);
		pthread_exit((void *)13);
	}

	if (getvalue != value) {
		printf("getvalue not valid, getvalue=%d",
		       (unsigned int)(uintptr_t)getvalue);
		pthread_exit((void *)68);
	}

	pthread_exit((void *)0);
}

void destr_fn(void *parm)
{
	printf("Destructor function invoked\n");
	free(parm);
}

int demo_setspecific_main()
{
	int status;
	int i;
	int threadparm[threads];
	pthread_t threadid[threads];
	int thread_stat[threads];

	if ((status = pthread_key_create(&key, destr_fn)) < 0) {
		printf("pthread_key_create failed, errno=%d", errno);
		exit(1);
	}

	for (i = 0; i < threads; i++) {
		threadparm[i] = i + 1;
		status = pthread_create(&threadid[i], NULL, threadfunc,
					(void *)&threadparm[i]);
		if (status < 0) {
			printf("pthread_create failed, errno=%d", errno);
			exit(2);
		}
	}

	for (i = 0; i < threads; i++) {
		status = pthread_join(threadid[i], (void *)&thread_stat[i]);
		if (status < 0) {
			printf("pthread_join failed, thread %d, errno=%d\n",
			       i + 1, errno);
		}

		if (thread_stat[i] != 0) {
			printf("bad thread status, thread %d, status=%d\n",
			       i + 1, thread_stat[i]);
		}
	}
	exit(EXIT_SUCCESS);
}
