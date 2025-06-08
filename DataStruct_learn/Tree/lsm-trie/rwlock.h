/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */
#pragma once

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

struct ReaderLock {
	// 读计数值
	uint64_t nr_readers;
	// 允许读状态
	bool open;
	// 条件变量
	pthread_cond_t cond_reader;
	uint64_t pad1[8];
};

struct RWLock {
	// 线程互斥锁
	pthread_mutex_t mutex_any;
	// 准备写计数器
	uint64_t next_ticket; // sell to writers
	// 读锁位置
	uint64_t reader_ticket;
	// 写完成计数器
	uint64_t writer_ticket;
	uint64_t pad1[8];
	// 条件变量
	pthread_cond_t cond_writer;
	uint64_t pad2[8];
	struct ReaderLock rl[2]; // mod 2
};

void rwlock_show(struct RWLock *bo);
void rwlock_initial(struct RWLock *bo);
uint64_t rwlock_reader_lock(struct RWLock *bo);
void rwlock_reader_unlock(struct RWLock *bo, const uint64_t ticket);
uint64_t rwlock_writer_lock(struct RWLock *bo);
void rwlock_writer_unlock(struct RWLock *bo, const uint64_t ticket);
