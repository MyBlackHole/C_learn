/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "mempool.h"
#include "stat.h"

struct BloomFilter {
	// 可以存大小
	uint32_t bytes; // bytes = bits >> 3 (length of filter)
	// 键计数器
	uint32_t nr_keys;
	// 映射内存
	uint8_t filter[];
};

// compact bloom_table
// format: encoded bits, bits
#define BLOOMTABLE_INTERVAL ((16u))
struct BloomTable {
	// 布隆过滤器内存指针
	uint8_t *raw_bf;
	// 布隆过滤器个数
	uint32_t nr_bf;
	// 所有布隆过滤器总大小
	uint32_t nr_bytes; // size of raw_bf
	// 每 16 个布隆过滤器间隔的内存大小
	uint32_t offsets[];
};

// Container: storing boxes for multiple tables
// Box: multiple related bloom-filter in one box
struct BloomContainer {
	int raw_fd;
	uint64_t off_raw; // === off_main in MetaFileHeader
	uint32_t nr_barrels; // === nr_main
	uint32_t nr_bf_per_box; // 1 -- 8
	// 桶个数
	uint32_t nr_index;
	uint64_t mtid;
	// 每个桶 id
	uint16_t index_last[]; // the LAST barrel_id in each box
};

struct BloomFilter *bloom_create(const uint32_t nr_keys,
				 struct Mempool *const mempool);

void bloom_update(struct BloomFilter *const bf, const uint64_t hv);

bool bloom_match(const struct BloomFilter *const bf, const uint64_t hv);

struct BloomTable *bloomtable_build(struct BloomFilter *const *const bfs,
				    const uint64_t nr_bf);

bool bloomtable_dump(struct BloomTable *const bt, FILE *fo);

struct BloomTable *bloomtable_load(FILE *const fi);

bool bloomtable_match(struct BloomTable *const bt, const uint32_t index,
		      const uint64_t hv);

void bloomtable_free(struct BloomTable *const bt);

struct BloomContainer *bloomcontainer_build(struct BloomTable *const bt,
					    const int raw_fd,
					    const uint64_t off_raw,
					    struct Stat *const stat);

struct BloomContainer *bloomcontainer_update(struct BloomContainer *const bc,
					     struct BloomTable *const bt,
					     const int new_raw_fd,
					     const uint64_t new_off_raw,
					     struct Stat *const stat);

bool bloomcontainer_dump_meta(struct BloomContainer *const bc, FILE *const fo);

struct BloomContainer *bloomcontainer_load_meta(FILE *const fi,
						const int raw_fd);

uint64_t bloomcontainer_match(struct BloomContainer *const bc,
			      const uint32_t index, const uint64_t hv);

void bloomcontainer_free(struct BloomContainer *const bc);
