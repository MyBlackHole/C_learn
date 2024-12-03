// 一个使用读写锁来实现 4 个线程读写一段数据是实例。
// 在此示例程序中，共创建了 4 个线程，
// 其中两个线程用来写入数据，两个线程用来读取数据
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_rwlock_t rwlock; // 读写锁
int num_1 = 1;

// 读操作，其他线程允许读操作，却不允许写操作
void *rwlocak_test1(void *arg)
{
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("read num_1 first == %d\n", num_1);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

// 读操作，其他线程允许读操作，却不允许写操作
void *rwlocak_test2(void *arg)
{
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("read num_1 second == %d\n", num_1);
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
	}
}

// 写操作，其它线程都不允许读或写操作
void *wrlock_test1(void *arg)
{
	while (1) {
		pthread_rwlock_wrlock(&rwlock);
		num_1++;
		printf("write thread first\n");
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
	}
}

// 写操作，其它线程都不允许读或写操作
void *wrlock_test2(void *arg)
{
	while (1) {
		pthread_rwlock_wrlock(&rwlock);
		num_1++;
		printf("write thread second\n");
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

int demo_rwlock_main()
{
	pthread_t ptd1;
	pthread_t ptd2;
	pthread_t ptd3;
	pthread_t ptd4;

	pthread_rwlock_init(&rwlock, NULL); // 初始化一个读写锁

	// 创建线程
	pthread_create(&ptd1, NULL, rwlocak_test1, NULL);
	pthread_create(&ptd2, NULL, rwlocak_test2, NULL);
	pthread_create(&ptd3, NULL, wrlock_test1, NULL);
	pthread_create(&ptd4, NULL, wrlock_test2, NULL);

	// 等待线程结束，回收其资源
	pthread_join(ptd1, NULL);
	pthread_join(ptd2, NULL);
	pthread_join(ptd3, NULL);
	pthread_join(ptd4, NULL);

	pthread_rwlock_destroy(&rwlock); // 销毁读写锁

	return 0;
}
