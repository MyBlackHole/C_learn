#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int demo_rwlock1_main()
{
	pthread_rwlock_t rwl;
	printf("init: %d\n", pthread_rwlock_init(&rwl, NULL));
	printf("wrlock: %d\n", pthread_rwlock_wrlock(&rwl));
	printf("rdlock: %d\n", pthread_rwlock_rdlock(&rwl));

	printf("unlock: %d\n", pthread_rwlock_unlock(&rwl));
	printf("unlock: %d\n", pthread_rwlock_unlock(&rwl));

	printf("wrlock: %d\n", pthread_rwlock_wrlock(&rwl));
	printf("unlock: %d\n", pthread_rwlock_unlock(&rwl));

	pthread_rwlock_destroy(&rwl); // 销毁读写锁
	return EXIT_SUCCESS;
}
