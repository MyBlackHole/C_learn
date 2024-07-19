/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */

#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE

#include "rwlock.h"

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

void rwlock_show(struct RWLock *bo)
{
	printf("****nxt %lu r %lu w %lu r0 %c %lu r1 %c %lu\n", bo->next_ticket,
	       bo->reader_ticket, bo->writer_ticket, bo->rl[0].open ? '+' : '_',
	       bo->rl[0].nr_readers, bo->rl[1].open ? '+' : '_',
	       bo->rl[1].nr_readers);
}

// RWLock 初始化
void rwlock_initial(struct RWLock *bo)
{
	bo->next_ticket = 0;
	bo->reader_ticket = 0;
	bo->writer_ticket = 0;
	// 互斥锁初始化
	pthread_mutex_init(&(bo->mutex_any), NULL);
	// 条件变量初始化
	pthread_cond_init(&(bo->cond_writer), NULL);

	bo->rl[0].nr_readers = 0;
	bo->rl[1].nr_readers = 0;

	// 条件变量初始化
	pthread_cond_init(&(bo->rl[0].cond_reader), NULL);
	pthread_cond_init(&(bo->rl[1].cond_reader), NULL);
	bo->rl[0].open = true; // open 0
	bo->rl[1].open = false; // close 1
}

uint64_t rwlock_reader_lock(struct RWLock *bo)
{
	pthread_mutex_lock(&(bo->mutex_any));
	// buy one reader-ticket
	const uint64_t ticket = bo->reader_ticket;
	// find the room and line up
	struct ReaderLock *const rl = &(bo->rl[ticket & 1]);
	// 准备读加一
	rl->nr_readers++;
	// 等于 false 正在写，等待写结束
	while (rl->open == false) { // wait for open
		// 等待唤醒
		pthread_cond_wait(&(rl->cond_reader), &(bo->mutex_any));
	}
	// do what you want
	pthread_mutex_unlock(&(bo->mutex_any));
	return ticket;
}

void rwlock_reader_unlock(struct RWLock *bo, const uint64_t ticket)
{
	pthread_mutex_lock(&(bo->mutex_any));
	struct ReaderLock *const rl = &(bo->rl[ticket & 1]);
	assert(rl->nr_readers);
	// leave
	// 读完成减一
	rl->nr_readers--;
	// if I'm the last, wake up the writer
	if (rl->nr_readers == 0) {
		// 唤醒写堵塞线程
		pthread_cond_broadcast(&(bo->cond_writer));
	}
	pthread_mutex_unlock(&(bo->mutex_any));
}

uint64_t rwlock_writer_lock(struct RWLock *bo)
{
	pthread_mutex_lock(&(bo->mutex_any));
	// early register as writer
	// buy one writer-ticket
	const uint64_t ticket = bo->next_ticket;
	// 准备写
	bo->next_ticket++;
	// wait for my writer-ticket
	// 是否有准备写的线程, 不等于就是有
	while (ticket != bo->writer_ticket) {
		// 唤醒其他准备写的线程
		pthread_cond_wait(&(bo->cond_writer), &(bo->mutex_any));
	}
	// tell readers to go to next room
	assert(bo->reader_ticket == bo->writer_ticket);

	// 读锁位置加一
	bo->reader_ticket++;
	// close door
	struct ReaderLock *const rl = &(bo->rl[ticket & 1]);
	// wait for readers to leave
	// 读未全完成继续堵塞写
	while (rl->nr_readers > 0) {
		pthread_cond_wait(&(bo->cond_writer), &(bo->mutex_any));
	}
	rl->open = false;
	// work time
	pthread_mutex_unlock(&(bo->mutex_any));
	return ticket;
}

void rwlock_writer_unlock(struct RWLock *bo, const uint64_t ticket)
{
	pthread_mutex_lock(&(bo->mutex_any));
	struct ReaderLock *const rl_curr = &(bo->rl[ticket & 1]);
	assert(rl_curr->nr_readers == 0);
	// work done. only now can open next door
	struct ReaderLock *const rl_next = &(bo->rl[(ticket + 1) & 1]);
	rl_next->open = true;
	// 唤醒读堵塞线程
	if (rl_next->nr_readers > 0) {
		pthread_cond_broadcast(&(rl_next->cond_reader));
	}
	// wake up next writer
	// 写结束了 writer_ticket 加一
	bo->writer_ticket++;
	// wake up writers anyway
	// 唤醒写堵塞线程
	pthread_cond_broadcast(&(bo->cond_writer));
	pthread_mutex_unlock(&(bo->mutex_any));
}
