#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREAD 100

void *thread_create_test_inc(void *arg);
void *thread_create_test_des(void *arg);
long long num_3 = 0;

int demo_create2_main(int argc, char *argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int index;

	printf("sizeof long long: %lu \n", sizeof(long long));
	for (index = 0; index < NUM_THREAD; index++) {
		if (index % 2) {
			pthread_create(&(thread_id[index]), NULL,
				       thread_create_test_inc, NULL);
		} else {
			pthread_create(&(thread_id[index]), NULL,
				       thread_create_test_des, NULL);
		}
	}

	for (index = 0; index < NUM_THREAD; index++) {
		pthread_join(thread_id[index], NULL);
	}

	printf("result: %lld \n", num_3);
	return 0;
}

void *thread_create_test_inc(void *arg)
{
	int index;
	for (index = 0; index < 50000000; index++) {
		num_3 += 1;
	}
	return NULL;
}
void *thread_create_test_des(void *arg)
{
	int index;
	for (index = 0; index < 50000000; index++) {
		num_3 -= 1;
	}
	return NULL;
}
