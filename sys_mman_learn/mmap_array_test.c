#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include <stdatomic.h>

#define CACHE_SIZE 32 // 缓存块数量
#define CHUNK_SIZE (4 * 1024 * 1024) // 4MB/块
#define ELEMENT_TYPE double
#define ELEMENT_SIZE sizeof(ELEMENT_TYPE)

// 分块描述符（线程安全增强版）
struct Chunk {
	void *addr; // 内存地址
	off_t file_offset; // 文件偏移
	atomic_int ref_count; // 原子引用计数
	atomic_long last_access; // 原子最后访问时间
	pthread_rwlock_t rwlock; // 块级读写锁
	int is_dirty; // 脏标记（受cache_lock保护）
};

// 数组管理器（全局锁保护关键元数据）
struct BlockedArray {
	int fd; // 文件描述符
	size_t total_elements; // 总元素数
	size_t elements_per_chunk; // 每块元素数
	struct Chunk cache[CACHE_SIZE];
	pthread_mutex_t cache_lock; // 全局缓存锁
};

// 初始化数组（线程安全）
struct BlockedArray *create_array(const char *filename, size_t n)
{
	struct BlockedArray *arr = calloc(1, sizeof(struct BlockedArray));
	if (!arr)
		return NULL;

	memset(arr, 0, sizeof(struct BlockedArray));

	// 初始化全局锁
	pthread_mutex_init(&arr->cache_lock, NULL);

	// 创建/打开文件
	arr->fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (arr->fd == -1)
		goto error;

	// 扩展文件
	arr->total_elements = n;
	size_t file_size = n * ELEMENT_SIZE;
	if (ftruncate(arr->fd, file_size) == -1)
		goto error;

	// 初始化块参数
	arr->elements_per_chunk = CHUNK_SIZE / ELEMENT_SIZE;
	for (int i = 0; i < CACHE_SIZE; i++) {
		pthread_rwlock_init(&arr->cache[i].rwlock, NULL);
	}
	return arr;

error:
	perror("初始化失败");
	if (arr->fd != -1)
		close(arr->fd);
	free(arr);
	return NULL;
}

// 线程安全的LRU淘汰算法
struct Chunk *find_victim_chunk(struct BlockedArray *arr)
{
	struct Chunk *victim = NULL;
	long oldest = LONG_MAX;

	pthread_mutex_lock(&arr->cache_lock);

	for (int i = 0; i < CACHE_SIZE; i++) {
		// 跳过正在使用的块（ref_count > 0）
		if (arr->cache[i].ref_count == 0 &&
		    atomic_load(&arr->cache[i].last_access) < oldest) {
			oldest = atomic_load(&arr->cache[i].last_access);
			victim = &arr->cache[i];
		}
	}

	if (victim && victim->addr) {
		if (victim->is_dirty) {
			msync(victim->addr, CHUNK_SIZE, MS_SYNC);
			victim->is_dirty = 0;
		}
		munmap(victim->addr, CHUNK_SIZE);
		victim->addr = NULL;
	}

	pthread_mutex_unlock(&arr->cache_lock);
	return victim;
}

// 线程安全的块加载
struct Chunk *load_chunk(struct BlockedArray *arr, off_t file_offset)
{
	struct Chunk *victim = find_victim_chunk(arr);
	if (!victim)
		return NULL;

	// 映射新块（受全局锁保护）
	pthread_mutex_lock(&arr->cache_lock);
	void *addr = mmap(NULL, CHUNK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
			  arr->fd, file_offset);
	if (addr == MAP_FAILED) {
		pthread_mutex_unlock(&arr->cache_lock);
		return NULL;
	}

	victim->addr = addr;
	victim->file_offset = file_offset;
	atomic_store(&victim->last_access, time(NULL));
	atomic_store(&victim->ref_count, 0);
	pthread_mutex_unlock(&arr->cache_lock);
	return victim;
}

// 安全的元素访问（返回前增加引用计数）
ELEMENT_TYPE *get_element(struct BlockedArray *arr, size_t index, int write)
{
	if (index >= arr->total_elements)
		return NULL;

	// 计算块位置
	size_t chunk_idx = index / arr->elements_per_chunk;
	off_t file_offset = chunk_idx * CHUNK_SIZE;

	// 查找或加载块（线程安全）
	struct Chunk *chunk = NULL;
	pthread_mutex_lock(&arr->cache_lock);
	for (int i = 0; i < CACHE_SIZE; i++) {
		if (arr->cache[i].file_offset == file_offset &&
		    arr->cache[i].addr) {
			chunk = &arr->cache[i];
			break;
		}
	}

	if (!chunk) {
		pthread_mutex_unlock(&arr->cache_lock);
		chunk = load_chunk(arr, file_offset);
		if (!chunk)
			return NULL;
		pthread_mutex_lock(&arr->cache_lock);
	}

	atomic_fetch_add(&chunk->ref_count, 1); // 增加引用计数
	pthread_mutex_unlock(&arr->cache_lock);

	// 加读写锁
	if (write)
		pthread_rwlock_wrlock(&chunk->rwlock);
	else
		pthread_rwlock_rdlock(&chunk->rwlock);

	// 计算元素地址
	size_t offset = (index % arr->elements_per_chunk) * ELEMENT_SIZE;
	return (ELEMENT_TYPE *)((char *)chunk->addr + offset);
}

// 释放元素（减少引用计数）
void release_element(struct BlockedArray *arr, ELEMENT_TYPE *elem,
		     int mark_dirty)
{
	// 通过指针反向查找块（实际项目需优化）
	struct Chunk *chunk = NULL;

	for (int i = 0; i < CACHE_SIZE; i++) {
		if (arr->cache[i].addr <= (void *)elem &&
		    (void *)elem < arr->cache[i].addr + CHUNK_SIZE) {
			chunk = &arr->cache[i];
			break;
		}
	}

	if (!chunk)
		return;

	// 释放读写锁
	pthread_rwlock_unlock(&chunk->rwlock);

	// 更新脏标记和引用计数
	pthread_mutex_lock(&arr->cache_lock);
	if (mark_dirty)
		chunk->is_dirty = 1;
	atomic_fetch_sub(&chunk->ref_count, 1);
	atomic_store(&chunk->last_access, time(NULL));
	pthread_mutex_unlock(&arr->cache_lock);
}

// 销毁数组（线程安全）
void destroy_array(struct BlockedArray *arr)
{
	pthread_mutex_lock(&arr->cache_lock);
	for (int i = 0; i < CACHE_SIZE; i++) {
		if (arr->cache[i].addr) {
			if (arr->cache[i].is_dirty)
				msync(arr->cache[i].addr, CHUNK_SIZE, MS_SYNC);
			munmap(arr->cache[i].addr, CHUNK_SIZE);
			pthread_rwlock_destroy(&arr->cache[i].rwlock);
		}
	}
	close(arr->fd);
	pthread_mutex_unlock(&arr->cache_lock);
	pthread_mutex_destroy(&arr->cache_lock);
	free(arr);
}

// 示例：多线程累加操作
#define N_THREADS 8
#define ARRAY_SIZE (1UL << 10) // 10亿元素（约8GB）

void *sum_thread(void *arg)
{
	struct BlockedArray *arr = arg;
	double local_sum = 0;

	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		/*if (i % N_THREADS != (size_t)arg)*/
		/*	continue; // 分片处理*/

		double *elem = get_element(arr, i, 0);
		local_sum += *elem;
		release_element(arr, elem, 0);
	}

	return (void *)(uintptr_t)local_sum;
}

int demo_mmap_array_main()
{
	double total = 0;
	struct BlockedArray *arr = create_array("data.bin", ARRAY_SIZE);

	// 初始化数据（示例简化）
	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		double *elem = get_element(arr, i, 1);
		*elem = i * 0.01;
		release_element(arr, elem, 1);
	}

	total = (double)(uintptr_t)sum_thread(arr);

	/*// 启动并行计算线程*/
	/*pthread_t threads[N_THREADS];*/
	/*for (int i = 0; i < N_THREADS; i++) {*/
	/*	pthread_create(&threads[i], NULL, sum_thread,*/
	/*		       (void *)(uintptr_t)i);*/
	/*}*/
	/**/
	/*// 汇总结果*/
	/*for (int i = 0; i < N_THREADS; i++) {*/
	/*	void *ret;*/
	/*	pthread_join(threads[i], &ret);*/
	/*	total += (double)(uintptr_t)ret;*/
	/*}*/
	printf("总和: %.2f\n", total);

	destroy_array(arr);
	return 0;
}

/*gcc -O3 -pthread -march=native -D_GNU_SOURCE mmap_test.c -o mmap_test*/
