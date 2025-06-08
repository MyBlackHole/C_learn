#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 测试空对象锁的读锁
int demo_rwlock3_main()
{
	pthread_rwlock_t rwl;
	pthread_rwlock_t *p_rwl = &rwl;
	// pthread_rwlock_t *p_rwl = NULL;
	printf("rdlock: %d\n", pthread_rwlock_rdlock(p_rwl));
	return EXIT_SUCCESS;
}

// output:
// 段异常
