#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 声明一个读写锁变量
static pthread_rwlock_t rwlock;

// 共享的数据
int shared_data = 0;

// 读线程的函数
void *reader2(void *arg)
{
	while (1) {
		// 读线程尝试获取读锁
		pthread_rwlock_rdlock(&rwlock);
		// 读取共享数据
		printf("Reader: %d\n", shared_data);
		// 释放读锁
		pthread_rwlock_unlock(&rwlock);
		// 等待一秒钟再次读取
		sleep(1);
	}
}

// 写线程的函数
void *writer2(void *arg)
{
	while (1) {
		// 写线程尝试获取写锁
		pthread_rwlock_wrlock(&rwlock);
		// 修改共享数据（增加）
		shared_data++;
		printf("Writer: Incremented shared_data to %d\n", shared_data);
		// 释放写锁
		pthread_rwlock_unlock(&rwlock);
		// 等待两秒钟再次写入
		sleep(2);
	}
}

int demo_rwlock2_main()
{
	// 创建读线程和写线程的线程句柄
	pthread_t reader_thread, writer_thread;

	// 初始化读写锁
	pthread_rwlock_init(&rwlock, NULL);

	// 创建并启动读线程和写线程
	pthread_create(&reader_thread, NULL, reader2, NULL);
	pthread_create(&writer_thread, NULL, writer2, NULL);

	// 等待读线程和写线程结束
	pthread_join(reader_thread, NULL);
	pthread_join(writer_thread, NULL);

	// 销毁读写锁
	pthread_rwlock_destroy(&rwlock);

	return 0;
}
