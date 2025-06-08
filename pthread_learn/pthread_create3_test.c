#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define COUNT 10000

static int index;

void *thread_create_test_func3(void *arg)
{
	for (int j = 0; j < COUNT; j++) {
		index++;
	}
	pthread_exit(0);
}

int demo_create3_main(void)
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1, NULL, thread_create_test_func3, NULL);
	pthread_create(&tid2, NULL, thread_create_test_func3, NULL);
	printf("pthread tid1=%lu; pthread tid1=%lu\n", tid1, tid2);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("%d\n", index);
	return 0;
}
// 会出现不等于 20000
// out:
// 19996
