/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */

#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE

#include "cmap.h"

#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <linux/fs.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "generator.h"
#include "table.h"

// 表大小
// 32MB
#define CONTAINER_UNIT_SIZE ((TABLE_ALIGN))

// 打开 raw_fn 返回文件描述符
static int containermap_open_raw(const char *const raw_fn, const off_t cap_hint)
{
	struct stat rawst;
	assert(raw_fn);
	// test filename
	const int rst0 = stat(raw_fn, &rawst);

	int raw_fd = -1;
	// blk device
	if ((rst0 == 0) && S_ISBLK(rawst.st_mode)) {
		// 块设备流程
		// O_DIRECT 无缓存
		// O_SYNC 同步
		// O_LARGEFILE 大文件
		// O_RDWR 读写
		const int blk_flags = O_RDWR | O_LARGEFILE | O_SYNC | O_DIRECT;
		// 打开
		raw_fd = open(raw_fn, blk_flags);
		if (raw_fd < 0) {
			return -1;
		}
	} else { // is a normal file anyway
		// 字符文件流程
		// O_LARGEFILE 大文件
		// O_RDWR 读写
		// O_CREAT 不存在创建, 创建权限 644
		const int normal_flags = O_CREAT | O_RDWR | O_LARGEFILE;
		raw_fd = open(raw_fn, normal_flags, 00644);
		if (raw_fd < 0) {
			return -1;
		}
		const int rst1 = stat(raw_fn, &rawst);
		assert(rst1 == 0);
		// 小于 cap_hint 扩充大小
		if (rawst.st_size < cap_hint) { // increase file size
			// 截断文件使其大小为 cap_hint
			const int rt = ftruncate(raw_fd, cap_hint);
			if (rt != 0) {
				return -1;
			}
		}
	}
	// 返回文件描述符
	return raw_fd;
}

// nr_units, total_cap, discard
// 设置容器映射参数, 返回 true 正常、false 不正常
static bool containermap_probe(struct ContainerMap *const cm, const int raw_fd)
{
	struct stat st;
	assert(raw_fd >= 0);
	// 读取
	const int r = fstat(raw_fd, &st);
	assert(0 == r);

	if (S_ISBLK(st.st_mode)) { // block device
		// 块设备
		// 获取设备块大小 bytes, 赋值给 &cm->total_cap
		ioctl(raw_fd, BLKGETSIZE64, &(cm->total_cap));
		cm->discard = true;
	} else { // regular file
		// 获取文件大小
		cm->total_cap = st.st_size;
		cm->discard = false;
	}
	cm->nr_units = cm->total_cap / CONTAINER_UNIT_SIZE;
	return (cm->nr_units > 0) && (cm->total_cap > 0);
}

// 创建映射结构体并初始化
struct ContainerMap *containermap_create(const char *const raw_fn,
					 const uint64_t cap_hint)
{
	// 创建容器映射结构体, 初始化
	struct ContainerMap cm0;
	bzero(&cm0, sizeof(cm0));
	assert(sizeof(off_t) == sizeof(uint64_t));

	// 打开返回文件描述符， 字符文件的话确保大于 cap_hint
	const int raw_fd = containermap_open_raw(raw_fn, (off_t)cap_hint);
	if (raw_fd < 0) {
		return NULL;
	}

	// 初始化 true 成功， false 失败
	const bool rp = containermap_probe(&cm0, raw_fd);
	if (rp == false) {
		return NULL;
	}

	// 右移 3 位 bytes 映射大小
	const size_t nr_bytes = (cm0.nr_units + 7u) >> 3;
	struct ContainerMap *const cm =
		(typeof(cm))malloc(sizeof(*cm) + nr_bytes);
	// 初始化
	bzero(cm, sizeof(*cm) + nr_bytes);
	cm->nr_units = cm0.nr_units;
	cm->nr_used = 0;
	cm->total_cap = cm0.total_cap;
	cm->discard = cm0.discard;
	cm->raw_fd = raw_fd;
	pthread_mutex_init(&(cm->mutex_cm), NULL);

	return cm;
}

// containermap_dump 的逆过程
struct ContainerMap *containermap_load(const char *const meta_fn,
				       const char *const raw_fn)
{
	assert(meta_fn);
	// 打开文件
	FILE *const cmap_in = fopen(meta_fn, "rb");
	if (cmap_in == NULL) {
		return NULL;
	}

	// 1: nr_units
	uint64_t nr_units = 0;
	const size_t nun = fread(&nr_units, sizeof(nr_units), 1, cmap_in);
	assert(nun == 1);
	assert(nr_units > 0);
	// device smaller than CM

	// get device
	struct ContainerMap cm0;
	bzero(&cm0, sizeof(cm0));
	const int raw_fd =
		containermap_open_raw(raw_fn, nr_units * CONTAINER_UNIT_SIZE);
	assert(raw_fd >= 0);
	const bool rp = containermap_probe(&cm0, raw_fd);
	assert(rp == true);
	// check if cap fits
	assert(cm0.nr_units >= nr_units);

	const size_t nr_bytes = (nr_units + 7) >> 3;
	struct ContainerMap *const cm =
		(typeof(cm))malloc(sizeof(*cm) + nr_bytes);
	bzero(cm, sizeof(*cm) + nr_bytes);
	// 2: nr_used
	const size_t nus =
		fread(&(cm->nr_used), sizeof(cm->nr_used), 1, cmap_in);
	assert(nus == 1);
	// 3: bits
	const size_t nby =
		fread(cm->bits, sizeof(cm->bits[0]), nr_bytes, cmap_in);
	assert(nby == nr_bytes);
	// copy values
	cm->nr_units = nr_units;
	cm->total_cap = cm0.total_cap;
	cm->discard = cm0.discard;
	cm->raw_fd = raw_fd;
	pthread_mutex_init(&(cm->mutex_cm), NULL);
	fclose(cmap_in);
	return cm;
}

void containermap_dump(struct ContainerMap *const cm, const char *const meta_fn)
{
	assert(meta_fn);
	// 打开文件
	FILE *const cmap_out = fopen(meta_fn, "wb");
	assert(cmap_out);
	// 1: nr_units
	// 加锁
	pthread_mutex_lock(&(cm->mutex_cm));
	// 写入 cm->nr_units
	const size_t nun =
		fwrite(&(cm->nr_units), sizeof(cm->nr_units), 1, cmap_out);
	assert(nun == 1);
	// 写入 cm->nr_used
	const size_t nus =
		fwrite(&(cm->nr_used), sizeof(cm->nr_used), 1, cmap_out);
	assert(nus == 1);
	// 3: bits
	// 写入已经使用了的 cm->bits
	const size_t nr_bytes = (cm->nr_units + 7) >> 3;
	const size_t nby =
		fwrite(cm->bits, sizeof(cm->bits[0]), nr_bytes, cmap_out);
	assert(nby == nr_bytes);
	// 解锁
	pthread_mutex_unlock(&(cm->mutex_cm));
	// 关闭文件
	fclose(cmap_out);
}

// 打印使用状态
void containermap_show(struct ContainerMap *const cm)
{
	// 加锁
	pthread_mutex_lock(&(cm->mutex_cm));
	uint64_t ucount = 0;
	// HEADER
	static const char *XX = "--------------------------------";
	printf("Container Map\n  INDEX  /%s%s\\\n", XX, XX);
	// bits
	char line[256] = { 0 };
	for (uint64_t i = 0; i < cm->nr_units; i++) {
		// 获取位
		const uint8_t byte = cm->bits[i >> 3];
		const uint8_t bit = byte & (1u << (i & 7u));

		// line header
		if (i % 64u == 0) {
			sprintf(line, "%08lu:|", i);
		}

		line[10 + (i % 64u)] = (bit == 0) ? ' ' : '*';
		if (bit != 0) {
			ucount++;
		}

		// line end
		if (i % 64u == 63u) {
			line[10 + 64] = '\0';
			printf("%s|\n", line);
		}
	}
	if ((cm->nr_units % 64u) != 0) {
		uint64_t j = cm->nr_units;
		while ((j % 64u) != 0) {
			line[10 + (j % 64)] = '#';
			j++;
		}
		line[10 + 64] = '\0';
		printf("%s|\n", line);
	}
	printf("   END   \\%s%s/\n", XX, XX);
	printf("Container usage: (%lu/%lu, %.2lf%%)\n", ucount, cm->nr_units,
	       ((double)ucount) / ((double)cm->nr_units) * 100.0);
	// 解锁
	pthread_mutex_unlock(&(cm->mutex_cm));
	// 刷新缓存区
	fflush(stdout);
}

// return device offset within the reasonable range
// 分配空间
uint64_t containermap_alloc(struct ContainerMap *const cm)
{
	// 加锁
	pthread_mutex_lock(&(cm->mutex_cm));
	// 获取 64 位随机数
	const uint64_t rid = random_uint64();

	for (uint64_t i = 0; i < cm->nr_units; i++) {
		// 约束范围
		const uint64_t id = (i + rid) % cm->nr_units;

		// id 换算成字节与位
		const uint8_t byte = cm->bits[id >> 3];
		// byte & 防止访问过
		const uint8_t bit = byte & (1u << (id & 7u));

		if (bit == 0) { // hit
			// 设置对应位
			const uint8_t new_byte = byte | (1u << (id & 7u));
			cm->bits[id >> 3] = new_byte;
			// 计数器
			cm->nr_used++;
			// 解锁
			pthread_mutex_unlock(&(cm->mutex_cm));
			// 返回偏移
			return (id * CONTAINER_UNIT_SIZE);
		}
	}
	// full
	// 解锁
	pthread_mutex_unlock(&(cm->mutex_cm));
	// on full returning invalid offset > last byte
	// 返回无效偏移
	return (cm->nr_units + 100u) * CONTAINER_UNIT_SIZE;
}

// 释放分配
bool containermap_release(struct ContainerMap *const cm, const uint64_t offset)
{
	// 解锁
	pthread_mutex_lock(&(cm->mutex_cm));
	// offset 是 CONTAINER_UNIT_SIZE 倍数
	assert((offset & (CONTAINER_UNIT_SIZE - 1u)) == 0);
	// 整除获取余数
	const uint64_t id = offset / CONTAINER_UNIT_SIZE;
	assert(id < cm->nr_units);
	const uint8_t byte = cm->bits[id >> 3];
	const uint8_t new_byte = byte & (~(1u << (id & 7u)));
	assert(new_byte < byte);
	cm->bits[id >> 3] = new_byte;
	cm->nr_used--;
	if ((cm->discard == true) && (cm->raw_fd >= 0)) { // issue TRIM
		const uint64_t range[2] = { offset, CONTAINER_UNIT_SIZE };
		ioctl(cm->raw_fd, BLKDISCARD, range);
	}
	// 解锁
	pthread_mutex_unlock(&(cm->mutex_cm));
	return true;
}

// 释放 containermap
void containermap_destroy(struct ContainerMap *const cm)
{
	assert(cm);
	close(cm->raw_fd);
	free(cm);
}

// 未使用的
uint64_t containermap_unused(const struct ContainerMap *const cm)
{
	// 总的减去使用的
	return (cm->nr_units - cm->nr_used);
}
