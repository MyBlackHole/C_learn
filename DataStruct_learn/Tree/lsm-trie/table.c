/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */

#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE

#include "table.h"

#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <malloc.h>
#include <openssl/sha.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "bloom.h"
#include "coding.h"
#include "debug.h"
#include "mempool.h"
#include "stat.h"

// 4088
#define BARREL_CAP ((BARREL_ALIGN - sizeof(struct MetaIndex)))
#define TABLE_VOLUME_PERCENT ((0.75)) // reduce this for large values
// 元索引占比
#define METAINDEX_PERCENT ((0.99))
#define METAINDEX_MAX_NR ((UINT64_C(2048)))

struct Item {
	struct Item *next;
	// 移动次数
	uint16_t nr_moved;
	// 空间使用量
	uint16_t volume;
	// 键长度
	uint16_t klen;
	// 值长度
	uint16_t vlen;
	// 使用键计算出来的 hash
	uint8_t hash[HASHBYTES];
	uint8_t kv[]; // len(kv) == klen + vlen
};

// read-only (reference)
struct RawItem {
	uint16_t klen;
	uint16_t vlen;
	const uint8_t *pk;
	const uint8_t *pv;
	const uint8_t *limit;
};

#define BARREL_NR_HT ((64))

// 桶
struct Barrel { // a barrel of items
	// 链表数组
	struct Item *items[BARREL_NR_HT];
	// 容量
	uint16_t volume;
	uint16_t id;

	// 元素移动目标桶 id
	uint16_t rid; // == id if no overflown
	// 移出元素数量
	uint16_t nr_out;

	//
	uint32_t min;
};

struct MetaIndex {
	uint16_t id;
	uint16_t rid;
	uint32_t min;
} __attribute__((packed));

// 获取 hash 的后 8 位 uint8_t
static uint64_t __hash_bf(const uint8_t *const hash)
{
	const uint64_t *const phv = (typeof(phv))(&(hash[12]));
	const uint64_t hv = *phv;
	return hv;
}

// for bloom-filter
static inline uint64_t item_hash_bf(const struct Item *const item)
{
	return __hash_bf(item->hash);
}

static uint32_t __hash_order(const uint8_t *const hash, const uint16_t bid)
{
	assert(bid < TABLE_NR_BARRELS);
	const uint32_t *const phv = (typeof(phv))(&(hash[12]));
	const uint32_t hv = *phv;
	const uint16_t shift = bid % (sizeof(hv) * 8); // % 32
	const uint32_t hv1 = (hv << (shift)) | (hv >> (32 - shift));
	return hv1;
}

// for select items on moving
// hash id 计算
static inline uint32_t item_hash_order(const struct Item *const item,
				       const uint16_t bid)
{
	return __hash_order(item->hash, bid);
}

static uint32_t __hash_ht(const uint8_t *const hash)
{
	// 取后 32 位求余
	const uint32_t *const phv = (typeof(phv))(&(hash[16]));
	const uint32_t hv = (*phv) % BARREL_NR_HT;
	return hv;
}

// for barrel->items[?]
// 取后 32 位求余
static inline uint32_t item_hash_ht(const struct Item *const item)
{
	return __hash_ht(item->hash);
}

// 判断是否相同
static inline bool item_identical(const struct Item *const a,
				  const struct Item *const b)
{
	// 地址一致
	if (a == b) {
		return true;
	}
	// 键长度不同
	if (a->klen != b->klen) {
		return false;
	}
	return (memcmp(a->kv, b->kv, a->klen) == 0) ? true : false;
}

static inline int item_identical_key(const uint16_t klen,
				     const uint8_t *const pk,
				     const struct Item *const i)
{
	// 键长度不同
	if (klen != i->klen) {
		return false;
	}
	return (memcmp(pk, i->kv, klen) == 0) ? true : false;
}

// 删除 item
static uint16_t item_erase(struct Item **const items, struct Item *const item)
{
	struct Item **iter = items;
	while (*iter) {
		// 判断键是否一致
		const bool identical = item_identical(*iter, item);
		if (identical) {
			// remove
			const uint16_t victim_volume = (*iter)->volume;
			// 把 iter 指向下一个
			// 内存释放???
			*iter = (*iter)->next;
			// 返回一致 *iter 的大小
			return victim_volume;
		}
		// 不一致继续找下一个
		iter = &((*iter)->next);
	}
	return 0;
}

// return 0 if no eviction
// return the length of the victim item if replaced
// 返回 0 代表没有 item 情况下 添加 item
// 返回大于 0 代表 item 存在，删除后再添加 item
static inline uint16_t item_insert(struct Item **const items,
				   struct Item *const item)
{
	// erase (one) identical item
	// 有一致 item 时删除 item 返回 items 的 item 大小
	// 没有返回 0
	const uint16_t victim_volume = item_erase(items, item);
	// insert in front
	// 添加 item
	item->next = *items;
	(*items) = item;
	return victim_volume;
}

// 查询 key 对应 item
// 没有返回 NULL
static struct Item *item_lookup(struct Item *const items, const uint16_t klen,
				const uint8_t *const pk)
{
	struct Item *iter = items;
	while (iter) {
		// 键查询
		const bool identical = item_identical_key(klen, pk, iter);
		if (identical) {
			return iter;
		}
		// 循环
		iter = iter->next;
	}
	return NULL;
}

// return ptr to the end of raw bytes
// 把 item 数据写入 ptr, 返回下一个 uint8_t 的指针
static uint8_t *item_encode(struct Item *item, uint8_t *const ptr)
{
	uint8_t *const pklen = ptr;
	uint8_t *const pk = encode_uint16(pklen, item->klen);
	memcpy(pk, item->kv, item->klen);

	uint8_t *const pvlen = pk + item->klen;
	uint8_t *const pv = encode_uint16(pvlen, item->vlen);
	memcpy(pv, item->kv + item->klen, item->vlen);

	uint8_t *const pnext = pv + item->vlen;
	assert(item->volume == (pnext - ptr));
	return pnext;
}

// 根据 item 创建新的 kv 返回
static struct KeyValue *item_to_keyvalue(struct Item *const item)
{
	// make a copy using malloc
	// 键的长度加上值的长度加上对象大小
	const size_t msize = sizeof(struct KeyValue) + item->klen + item->vlen;
	// 分配内存
	struct KeyValue *const kv = (typeof(kv))malloc(msize);
	assert(kv);
	kv->klen = item->klen;
	kv->vlen = item->vlen;
	kv->pk = kv->kv;
	kv->pv = kv->kv + kv->klen;
	memcpy(kv->pk, item->kv, kv->klen + kv->vlen);
	return kv;
}

static bool rawitem_init(struct RawItem *const raw, const uint8_t *const ptr)
{
	assert(raw);
	assert(ptr);
	bzero(raw, sizeof(*raw));
	uint16_t klen = 0, vlen = 0;
	const uint8_t *const pk = decode_uint16(ptr, &klen);
	if ((pk == ptr) || (klen == 0)) {
		return false;
	}
	const uint8_t *const pvlen = pk + klen;
	const uint8_t *const pv = decode_uint16(pvlen, &vlen);
	// assume pv is ok
	raw->klen = klen;
	raw->vlen = vlen;
	raw->pk = pk;
	raw->pv = pv;
	raw->limit = ptr + ((long)BARREL_CAP);
	return true;
}

static bool rawitem_next(struct RawItem *const rawitem)
{
	const uint8_t *const pklen = rawitem->pv + rawitem->vlen;
	if (pklen >= rawitem->limit) {
		rawitem->klen = 0;
		rawitem->vlen = 0;
		return false;
	}
	uint16_t klen = 0, vlen = 0;
	const uint8_t *const pk = decode_uint16(pklen, &klen);
	if ((pk == pklen) || (klen == 0)) {
		return false;
	}
	const uint8_t *const pvlen = pk + klen;
	const uint8_t *const pv = decode_uint16(pvlen, &vlen);
	// assume pv is ok
	rawitem->klen = klen;
	rawitem->vlen = vlen;
	rawitem->pk = pk;
	rawitem->pv = pv;
	return true;
}

static struct KeyValue *rawitem_to_keyvalue(struct RawItem *const ri)
{
	// make a copy using malloc
	const size_t msize = sizeof(struct KeyValue) + ri->klen + ri->vlen;
	struct KeyValue *const kv = (typeof(kv))malloc(msize);
	assert(kv);
	kv->klen = ri->klen;
	kv->vlen = ri->vlen;
	kv->pk = kv->kv;
	kv->pv = kv->kv + kv->klen;
	memcpy(kv->pk, ri->pk, kv->klen);
	memcpy(kv->pv, ri->pv, kv->vlen);
	return kv;
}

// no hash!
static struct Item *rawitem_to_item(const struct RawItem *const ri,
				    struct Mempool *const mempool,
				    const uint8_t *const hash)
{
	assert(mempool);
	const size_t msize = sizeof(struct Item) + ri->klen + ri->vlen;
	struct Item *const item = (typeof(item))mempool_alloc(mempool, msize);
	if (item == NULL) {
		return NULL;
	}
	bzero(item, msize);
	// rb leave empty
	item->klen = ri->klen;
	item->vlen = ri->vlen;
	memcpy(item->kv, ri->pk, item->klen);
	memcpy(item->kv + item->klen, ri->pv, item->vlen);
	// SHA1
	if (hash) {
		memcpy(item->hash, hash, HASHBYTES);
	} else {
		SHA1(item->kv, item->klen, item->hash);
	}
	uint8_t buf[16];
	uint8_t *const p1 = encode_uint16(buf, item->klen);
	uint8_t *const p2 = encode_uint16(p1, item->vlen);
	const uint16_t volume = item->klen + item->vlen + (p2 - buf);
	item->volume = volume;
	return item;
}

// for insert
static struct Item *keyvalue_to_item(const struct KeyValue *const kv,
				     struct Mempool *const mempool)
{
	assert(mempool);
	const size_t msize = sizeof(struct Item) + kv->klen + kv->vlen;
	struct Item *const item = (typeof(item))mempool_alloc(mempool, msize);
	if (item == NULL) {
		return NULL;
	}
	bzero(item, msize);
	// rb leave empty
	item->klen = kv->klen;
	item->vlen = kv->vlen;
	// 填充 pk 长度 klen 到 item->kv
	memcpy(item->kv, kv->pk, item->klen);
	// 填充 pv 长度 vlen 到 item->kv 偏移 klen
	memcpy(item->kv + item->klen, kv->pv, item->vlen);
	// SHA1 计算，结果存入item->hash
	SHA1(item->kv, item->klen, item->hash);
	// 初始化编码 buf
	uint8_t buf[16];
	uint8_t *const p1 = encode_uint16(buf, item->klen);
	uint8_t *const p2 = encode_uint16(p1, item->vlen);
	// p2 - buf 是 klen 8 的整数倍加上 vlen 8 的整数倍
	// 17 就是 24
	// 空间使用量
	const uint16_t volume = item->klen + item->vlen + (p2 - buf);
	item->volume = volume;
	return item;
}

// 计算桶 item 总数
static uint16_t barrel_count(struct Barrel *const barrel)
{
	uint16_t count = 0;
	for (uint64_t i = 0; i < BARREL_NR_HT; i++) {
		struct Item *iter = barrel->items[i];
		while (iter) {
			count++;
			iter = iter->next;
		}
	}
	return count;
}

// 计算桶 item 总数 加上移动的总数
static uint16_t barrel_count_lookup(struct Barrel *const barrel)
{
	uint16_t count = 0;
	for (uint64_t i = 0; i < BARREL_NR_HT; i++) {
		struct Item *iter = barrel->items[i];
		while (iter) {
			count += (1 + iter->nr_moved);
			iter = iter->next;
		}
	}
	return count;
}

// 把桶数据填充到 items 里
static uint16_t barrel_to_array(struct Barrel *const barrel,
				struct Item **const items)
{
	uint16_t item_count = 0;
	for (uint64_t i = 0; i < BARREL_NR_HT; i++) {
		struct Item *iter = barrel->items[i];
		while (iter) {
			items[item_count++] = iter;
			iter = iter->next;
		}
	}
	// 返回桶数据个数总量
	return item_count;
}

static inline void barrel_erase(struct Barrel *const barrel,
				struct Item *const item)
{
	// 获取 id
	const uint32_t hid = item_hash_ht(item);
	// 删除 item 获取 item 大小
	const uint16_t volume = item_erase(&(barrel->items[hid]), item);
	// 移除删除 item 的大小
	barrel->volume -= volume;
}

static inline void barrel_insert(struct Barrel *const barrel,
				 struct Item *const item)
{
	// 取后 32 位求余
	const uint32_t hid = item_hash_ht(item);
	// 返回是否已经有存在一致 item 的大小
	const uint16_t victim_volume = item_insert(&(barrel->items[hid]), item);
	// 修改桶占用空间
	barrel->volume += item->volume;
	barrel->volume -= victim_volume;
}

// keyhead: need kv (only need key), klen
// 查询桶键为 pk 的元素并返回
// 没有返回 NULL
static inline struct Item *barrel_lookup(struct Barrel *const barrel,
					 const uint16_t klen,
					 const uint8_t *const pk,
					 const uint8_t *const hash)
{
	// 取出 32 位 hid
	const uint32_t hid = __hash_ht(hash);
	return item_lookup(barrel->items[hid], klen, pk);
}

// 把桶写入到 buffer 中, 返回写入的 item 数
static uint16_t barrel_dump_buffer(struct Barrel *const barrel,
				   uint8_t *const buffer)
{
	// serialize data
	uint8_t *ptr = buffer;
	// item 计数器
	uint16_t nr_items = 0;
	for (uint64_t i = 0; i < BARREL_NR_HT; i++) {
		// 获取列表首个 item
		struct Item *iter = barrel->items[i];
		// 遍历 item 列表
		while (iter) {
			uint8_t *const pnext = item_encode(iter, ptr);
			assert(pnext <= (buffer + (long)BARREL_CAP));
			// 循环
			ptr = pnext;
			// 取出下一个 item
			iter = iter->next;
			// 记录 item 写入 buffer 个数
			nr_items++;
		}
	}
	assert(ptr >= buffer);

	// get ride of valgrind warning
	if (ptr < (buffer + ((long)BARREL_CAP))) {
		// 不足 BARREL_CAP 部分清零
		bzero(ptr, (buffer + (long)BARREL_CAP) - ptr);
		// 设置数据间的边界
		ptr = encode_uint16(ptr, 0);
	}
	// put metadata
	ptr = buffer + ((long)BARREL_CAP);
	// 填充元索引数据到 ptr
	struct MetaIndex *const mi = (typeof(mi))ptr;
	mi->id = barrel->id;
	mi->rid = barrel->rid;
	mi->min = barrel->min;
	// 返回写入的 item 数
	return nr_items;
}

static void barrel_show(struct Barrel *const barrel, FILE *const fo)
{
	fprintf(fo, "[%4hu -> %4hu] %5hu %2hu %08x\n", barrel->id, barrel->rid,
		barrel->volume, barrel->nr_out, barrel->min);
}

static const struct MetaIndex *
__find_metaindex(const uint64_t nr_mi, const struct MetaIndex *const mis,
		 const uint16_t id)
{
	uint64_t lid = 0;
	uint64_t rid = nr_mi;
	while ((rid - lid) > 4) {
		const uint64_t mid = (lid + rid) >> 1;
		const struct MetaIndex *const mi = &(mis[mid]);
		if (mi->id == id) {
			break;
		} else if (mi->id > id) {
			rid = mid;
		} else { // mi->id < id
			lid = mid + 1;
		}
	}
	while ((lid < rid) && (mis[lid].id < id)) {
		lid++;
	}
	if ((lid < rid) && (mis[lid].id == id)) {
		return &(mis[lid]);
	} else {
		return NULL;
	}
}

// generate bloom-filter for a NORMAL barrel
// all bloom-filters should be generated before retaining
static struct BloomFilter *barrel_create_bf(struct Barrel *const barrel,
					    struct Mempool *const mempool)
{
	struct Item *items[BARREL_CAP] = { 0 };
	// 获取桶数据总量且填充数据到 items
	const uint16_t item_count = barrel_to_array(barrel, items);
	assert(item_count < BARREL_CAP);
	// 创建布隆过滤器
	struct BloomFilter *const bf = bloom_create(item_count, mempool);
	assert(bf);

	for (uint16_t i = 0; i < item_count; i++) {
		const uint64_t hv = item_hash_bf(items[i]);
		// 给布隆过滤器设置已经存在的键
		bloom_update(bf, hv);
	}
	// 返回布隆过滤器
	return bf;
}

// for table->barrels[?]
// 取第 5 个 8 位开始的后 13 位出来
uint16_t table_select_barrel(const uint8_t *const hash)
{
	// using the 4~7 bits of the hash value
	const uint8_t *const start_byte = &(hash[4]);
	const uint64_t hv = *((uint64_t *)start_byte);
	const uint16_t bid = (typeof(bid))(hv % TABLE_NR_BARRELS);
	return bid;
}

// 表初始化
static bool table_initial(struct Table *const table, const uint64_t capacity)
{
	// 最大桶数量空间大小
	const uint64_t main_space = sizeof(struct Barrel) * TABLE_MAX_BARRELS;
	assert(table->mempool);
	// 在内存池里分配内存, 返回内存的起始地址
	table->barrels = (typeof(table->barrels))mempool_alloc(table->mempool,
							       main_space);
	if (table->barrels == NULL) {
		return false;
	}
	// 桶内存初始化
	bzero(table->barrels, main_space);
	for (uint16_t i = 0u; i < TABLE_NR_BARRELS; i++) {
		table->barrels[i].id = i;
		table->barrels[i].rid = i;
	}

	table->volume = 0;
	table->capacity = capacity;
	table->bt = NULL;
	if (table->io_buffer == NULL) {
		table->io_buffer = huge_alloc(BARREL_ALIGN * TABLE_NR_IO);
		assert(table->io_buffer);
	}

	for (uint64_t i = 0; i < TABLE_ILOCKS_NR; i++) {
		// 互斥量初始化
		pthread_mutex_init(&(table->ilocks[i]), NULL);
	}
	return true;
}

// 表初始化
struct Table *table_alloc_new(const double cap_percent,
			      const double mempool_factor)
{
	// 分配内存
	struct Table *const table = (typeof(table))malloc(sizeof(*table));
	assert(table);
	// 初始化
	bzero(table, sizeof(*table));

	// 内存池创建
	const double cap_max = (double)(TABLE_NR_BARRELS * BARREL_CAP);
	const uint64_t msize = (uint64_t)(cap_max * mempool_factor);
	table->mempool = mempool_new(msize);

	const uint64_t cap_limit = (uint64_t)(cap_max * cap_percent);
	const bool ri = table_initial(table, cap_limit);
	assert(ri);
	return table;
}

// 默认表初始化方式
struct Table *table_alloc_default(const double mempool_factor)
{
	return table_alloc_new(TABLE_VOLUME_PERCENT, mempool_factor);
}

void table_free(struct Table *const table)
{
	mempool_free(table->mempool);
	if (table->io_buffer) {
		huge_free(table->io_buffer, BARREL_ALIGN * TABLE_NR_IO);
	}
	if (table->bt) {
		bloomtable_free(table->bt);
	}
	free(table);
}

// 是否大于表设置的阈值
bool table_full(const struct Table *const table)
{
	// 大于返回 true
	return (table->volume >= table->capacity) ? true : false;
}

// insert anyway
static void table_insert_item(struct Table *const table,
			      struct Item *const item)
{
	// assume hash value has been generated
	// 取 13 位 桶 id
	const uint16_t barrel_id = table_select_barrel(item->hash);
	// 取桶
	struct Barrel *const barrel = &table->barrels[barrel_id];
	const uint16_t vol0 = barrel->volume;
	// 把元素添加入桶
	barrel_insert(barrel, item);
	const uint16_t vol1 = barrel->volume;
	table->volume += (vol1 - vol0);
}

// thread safe insert (for compaction feed)
static void table_insert_item_mt(struct Table *const table,
				 struct Item *const item)
{
	const uint16_t barrel_id = table_select_barrel(item->hash);
	struct Barrel *const barrel = &table->barrels[barrel_id];
	pthread_mutex_lock(&(table->ilocks[barrel_id % TABLE_ILOCKS_NR]));
	const uint16_t vol0 = barrel->volume;
	barrel_insert(barrel, item);
	const uint16_t vol1 = barrel->volume;
	__sync_add_and_fetch(&(table->volume), (vol1 - vol0));
	pthread_mutex_unlock(&(table->ilocks[barrel_id % TABLE_ILOCKS_NR]));
}

static inline void table_insert_rawitem_mt(struct Table *const table,
					   const struct RawItem *const ri,
					   const uint8_t *const hash)
{
	struct Item *const item = rawitem_to_item(ri, table->mempool, hash);
	assert(item);
	table_insert_item_mt(table, item);
}

// not thread-safe!
// return false on full
bool table_insert_kv_safe(struct Table *const table,
			  const struct KeyValue *const kv)
{
	if (table_full(table)) {
		// 使用的空间大于最大分配空间
		// 退出
		return false;
	}
	struct Item *const item = keyvalue_to_item(kv, table->mempool);
	if (item == NULL) {
		// 退出
		return false;
	}
	// 给表添加元素， 允许重复添加
	table_insert_item(table, item);
	return true;
}

// build a BloomTable for itself
bool table_build_bloomtable(struct Table *const table)
{
	assert(table->bt == NULL);

	// 每个桶创建一个布隆过滤器
	// 同时根据桶 item 数据初始化
	struct BloomFilter *bfs[TABLE_NR_BARRELS];
	for (uint64_t i = 0; i < TABLE_NR_BARRELS; i++) {
		bfs[i] = barrel_create_bf(&(table->barrels[i]), table->mempool);
	}

	// 创建布隆过滤器表
	struct BloomTable *const bt = bloomtable_build(bfs, TABLE_NR_BARRELS);
	assert(bt);
	table->bt = bt;
	return true;
}

// 对表查询键 pk
struct KeyValue *table_lookup(struct Table *const table, const uint16_t klen,
			      const uint8_t *const pk,
			      const uint8_t *const hash)
{
	// 取出 id
	const uint16_t bid = table_select_barrel(hash);
	// 在 bid 对应的桶查询 pk 键
	struct Item *const item =
		barrel_lookup(&(table->barrels[bid]), klen, pk, hash);
	return item ? item_to_keyvalue(item) : NULL;
}

static inline int __compare_volume(const void *const p1, const void *const p2)
{
	struct Barrel *const b1 = *((typeof(&b1))p1);
	struct Barrel *const b2 = *((typeof(&b2))p2);
	if (b1->volume < b2->volume) {
		return -1;
	} else if (b1->volume > b2->volume) {
		return 1;
	} else {
		return 0;
	}
}

// 针对桶容量进行排序
static void retaining_sort_barrels_by_volume(struct Table *const table,
					     struct Barrel **barrels)
{
	// 填充桶数组
	for (uint64_t i = 0; i < TABLE_NR_BARRELS; i++) {
		barrels[i] = &(table->barrels[i]);
	}
	// 排序
	qsort(barrels, TABLE_NR_BARRELS, sizeof(barrels[0]), __compare_volume);
}

static int __compare_hash_order(const void *const p1, const void *const p2,
				void *const arg)
{
	struct Item *const i1 = *((typeof(&i1))p1);
	struct Item *const i2 = *((typeof(&i2))p2);
	uint64_t *const pbid = (typeof(pbid))arg;
	// item hash 与 桶 id 生成
	const uint32_t h1 = item_hash_order(i1, *pbid);
	const uint32_t h2 = item_hash_order(i2, *pbid);
	if (h1 < h2) {
		return -1;
	} else if (h1 > h2) {
		return 1;
	} else {
		return 0;
	}
}

// br 与 bl 是同指针且大于 BARREL_CAP, 会死循环!!!!!
static bool retaining_move_barrels(struct Barrel *const br,
				   struct Barrel *const bl)
{
	struct Item *ir[BARREL_ALIGN] __attribute__((aligned(8)));
	// 填充 ir 且返回桶数据个数
	const uint16_t nr_r = barrel_to_array(br, ir);
	// 对 ir 排序
	qsort_r(ir, nr_r, sizeof(ir[0]), __compare_hash_order, &(br->id));
	// 移动计数器
	uint64_t i = 0;
	while (br->volume > BARREL_CAP) {
		if (i >= nr_r) {
			return false;
		}
		// 删除桶里 ir[i] 元素
		barrel_erase(br, ir[i]);
		// 在 bl 桶添加元素
		barrel_insert(bl, ir[i]);
		ir[i]->nr_moved++;
		i++;
	}
	br->nr_out = i;
	br->rid = bl->id;
	assert(i < nr_r);
	br->min = item_hash_order(ir[i], br->id);
	return true;
}

// 均衡每个桶数据小于 BARREL_CAP
// 成功返回 true
static bool retaining_move_sorted(struct Barrel **const barrels)
{
	// 数组起始下标
	uint16_t lid = 0;
	// 数组结束下标
	uint16_t rid = TABLE_NR_BARRELS - 1;
	// 均衡桶数据量
	while ((barrels[rid]->volume > BARREL_CAP) && (lid < rid)) {
		assert(barrels[rid]->nr_out == 0);
		while (barrels[lid]->nr_out > 0) {
			// 进行过数据流动的跳过
			lid++;
		}
		if (lid >= rid) {
			// 遍历一轮内退出
			break;
		}
		struct Barrel *const br = barrels[rid];
		struct Barrel *const bl = barrels[lid];
		// 把符合条件的 br 元素移动到 bl
		const bool rm = retaining_move_barrels(br, bl);

		if (rm == false) {
			return false;
		}
		// 循环
		rid--;
		lid++;
	}

	if (barrels[rid]->volume > BARREL_CAP) {
		return false;
	} else {
		return true;
	}
}

// nr_out
static int __compare_out(const void *const p1, const void *const p2)
{
	struct Barrel *const b1 = *((typeof(&b1))p1);
	struct Barrel *const b2 = *((typeof(&b2))p2);
	// big -> small
	if (b1->nr_out < b2->nr_out) {
		return 1;
	} else if (b1->nr_out > b2->nr_out) {
		return -1;
	} else {
		return 0;
	}
}

// 获取未移动的数量
static uint64_t retaining_nr_todo(struct Table *const table)
{
	uint64_t nr_all = 0;
	uint64_t nr_out = 0;
	// 统计所有桶 item 总数, 移动 item 的总数
	for (uint64_t i = 0; i < TABLE_NR_BARRELS; i++) {
		// 累积单个桶 item 数量
		nr_all += barrel_count_lookup(&(table->barrels[i]));
		// 移动 item 的总数
		nr_out += table->barrels[i].nr_out;
	}
	const uint64_t nr_covered = nr_all - nr_out;
	const uint64_t nr_cover =
		(typeof(nr_cover))(((double)nr_all) * METAINDEX_PERCENT);
	const uint64_t nr_remains =
		(nr_cover > nr_covered) ? (nr_cover - nr_covered) : 0;
	return nr_remains;
}

static int __compare_id(const void *const p1, const void *const p2)
{
	const struct MetaIndex *const m1 = (typeof(m1))p1;
	const struct MetaIndex *const m2 = (typeof(m2))p2;
	if (m1->id < m2->id) {
		return -1;
	} else if (m1->id > m2->id) {
		return 1;
	} else {
		return 0;
	}
}

static void retaining_build_metaindex(struct Table *const table)
{
	// 创建桶数组，填充数据
	struct Barrel *barrels[TABLE_MAX_BARRELS];
	for (uint64_t i = 0; i < TABLE_NR_BARRELS; i++) {
		barrels[i] = &(table->barrels[i]);
	}
	// sort by out, big->small
	// 根据 nr_out 排序, 大到小
	qsort(barrels, TABLE_NR_BARRELS, sizeof(barrels[0]), __compare_out);
	// 获取未移动 item 数量
	uint64_t nr_todo = (typeof(nr_todo))retaining_nr_todo(table);

	// 创建元索引数组与初始化
	struct MetaIndex mi_buf[TABLE_MAX_BARRELS];
	bzero(mi_buf, sizeof(mi_buf[0]) * TABLE_MAX_BARRELS);
	// copy index
	uint64_t nr_mi = 0;
	for (uint64_t i = 0; i < METAINDEX_MAX_NR; i++) {
		struct Barrel *const barrel = barrels[i];
		mi_buf[i].id = barrel->id;
		mi_buf[i].rid = barrel->rid;
		mi_buf[i].min = barrel->min;
		nr_mi++;
		if (barrel->nr_out >= nr_todo) {
			break;
		}
		nr_todo -= barrel->nr_out;
	}
	// sort mi by id
	qsort(mi_buf, nr_mi, sizeof(mi_buf[0]), __compare_id);
	// set to table
	table->nr_mi = nr_mi;
	struct MetaIndex *const mis = (typeof(mis))mempool_alloc(
		table->mempool, sizeof(mis[0]) * nr_mi);
	assert(mis);
	memcpy(mis, mi_buf, sizeof(mis[0]) * nr_mi);
	table->mis = mis;
}

// 均衡数据，创建元索引
bool table_retain(struct Table *const table)
{
	uint64_t count = 0;
	while (true) {
		if (count >= 100) {
			// 限制均衡次数
			return false;
		}
		struct Barrel *barrels[TABLE_NR_BARRELS];
		// 填充数据到 barrels, 同时以 volume 为指标对 barrels 排序,
		retaining_sort_barrels_by_volume(table, barrels);
		if (barrels[TABLE_NR_BARRELS - 1]->volume <= BARREL_CAP) {
			// 均衡成功
			break; // done
		}
		// 均衡桶数据容量, 返回是否成功
		const bool rr = retaining_move_sorted(barrels);
		// 循环
		count++;
		if (rr == false) {
			// 均衡失败退出
			return false;
		}
	}
	// 创建元索引
	retaining_build_metaindex(table);
	return true;
}

// 把 table 写入 fd, 返回所有桶写入 item 总数
uint64_t table_dump_barrels(struct Table *const table, const int fd,
			    const uint64_t off)
{
	// 总写入 item 数
	uint64_t nr_all_items = 0;
	for (uint64_t j = 0; j < TABLE_NR_BARRELS; j += TABLE_NR_IO) {
		const uint64_t nr_dump =
			((j + TABLE_NR_IO) > TABLE_NR_BARRELS) ?
				(TABLE_NR_BARRELS - j) :
				TABLE_NR_IO;
		for (uint64_t i = 0; i < nr_dump; i++) {
			uint8_t *const ptr =
				&(table->io_buffer[BARREL_ALIGN * i]);
			// 把桶数据写入 ptr
			const uint64_t nr_items = barrel_dump_buffer(
				&(table->barrels[j + i]), ptr);
			// 计数器
			nr_all_items += nr_items;
		}
		if (nr_dump < TABLE_NR_IO) {
			// 未足部分清零
			bzero(&(table->io_buffer[BARREL_ALIGN * nr_dump]),
			      BARREL_ALIGN * (TABLE_NR_IO - nr_dump));
		}
		const size_t nr_bytes = (size_t)(TABLE_NR_IO * BARREL_ALIGN);
		const uint64_t off_j = off + (BARREL_ALIGN * j);
		// 写文件
		const ssize_t nw =
			pwrite(fd, table->io_buffer, nr_bytes, (off_t)(off_j));
		assert(nw == ((ssize_t)nr_bytes));
	}
	return nr_all_items;
}

bool table_dump_meta(struct Table *const table, const char *const metafn,
		     const uint64_t off)
{
	// 打开文件
	FILE *const fo = fopen(metafn, "wb");
	if (fo == NULL) {
		return false;
	}

	// dump header
	struct MetaFileHeader mfh;
	mfh.off = off;
	mfh.volume = table->volume;
	mfh.nr_mi = table->nr_mi;
	// 元文件头写入文件
	const size_t nw = fwrite(&mfh, sizeof(mfh), 1, fo);
	assert(nw == 1);

	// dump metadata
	// 元缩影数据写入文件
	const size_t nmo =
		fwrite(table->mis, sizeof(table->mis[0]), mfh.nr_mi, fo);
	assert(nmo == mfh.nr_mi);

	// dump BloomTable
	// 布隆过滤器持久化
	bloomtable_dump(table->bt, fo);
	// 关闭文件
	fclose(fo);
	return true;
}

void table_analysis_verbose(struct Table *const table, FILE *const out)
{
	// for all items
	uint32_t x_moved[128] = { 0 };
	uint16_t x_moved_max = 0;
	uint64_t x_moved_all = 0;
	uint64_t x_covered_all = 0;
	uint64_t x_lost_all = 0;
	uint64_t nr_mi = 0;
	uint64_t nr_meta = 0;
	uint16_t x_volume[4096 * 4] = { 0 };
	uint16_t x_volume_max = 0;
	uint64_t x_volume_all = 0;
	uint64_t count_lookup = 0;
	uint64_t count_items = 0;
	for (uint64_t bid = 0; bid < TABLE_NR_BARRELS; bid++) {
		struct Barrel *const barrel = &(table->barrels[bid]);
		uint16_t volume = 0;
		for (uint64_t hid = 0; hid < BARREL_NR_HT; hid++) {
			struct Item *iter = barrel->items[hid];
			while (iter) {
				x_moved[iter->nr_moved]++;
				x_moved_all += iter->nr_moved;
				if (iter->nr_moved > x_moved_max) {
					x_moved_max = iter->nr_moved;
				}
				volume += iter->volume;
				iter = iter->next;
			}
		}
		if (barrel->nr_out) {
			assert(barrel->id != barrel->rid);
			const struct MetaIndex *const mi = __find_metaindex(
				table->nr_mi, table->mis, barrel->id);
			if (mi) {
				nr_mi++;
				x_covered_all += barrel->nr_out;
			} else {
				x_lost_all += barrel->nr_out;
			}
			nr_meta++;
		} else {
			assert(barrel->id == barrel->rid);
		}
		assert(volume == barrel->volume);
		assert(volume < (4096 * 4));
		x_volume[volume]++;
		x_volume_all += volume;
		if (volume > x_volume_max) {
			x_volume_max = volume;
		}

		count_lookup += barrel_count_lookup(barrel);
		count_items += barrel_count(barrel);
	}
	assert(nr_mi == table->nr_mi);
	assert(x_volume_all == table->volume);
	assert(x_moved_all == (x_covered_all + x_lost_all));
	const double avg_read = ((double)(count_lookup - x_covered_all)) /
				((double)count_items);

	for (uint16_t i = 0; i <= x_moved_max; i++) {
		if (x_moved[i]) {
			fprintf(out, "M[%2hu] %4u\n", i, x_moved[i]);
		}
	}
	fprintf(out, "volume %lu capacity: %lu\n", table->volume,
		table->capacity);
	fprintf(out, "nr_mi %lu nr_meta %lu\n", table->nr_mi, nr_meta);
	fprintf(out, "covered %lu lost %lu\n", x_covered_all, x_lost_all);
	fprintf(out, "lookup %lu items %lu avg_read %.3lf\n", count_lookup,
		count_items, avg_read);
}

// 分析数据
void table_analysis_short(struct Table *const table, char *const buffer)
{
	if (table->nr_mi) {
		assert(table->mis);
	}
	const double vp =
		((double)table->volume) * 100.0 / ((double)TABLE_ALIGN);
	const double ik =
		((double)(table->nr_mi * sizeof(table->mis[0]))) / 1024.0;
	const uint32_t bt_bytes = table->bt ? table->bt->nr_bytes : 0u;
	const double bk =
		table->bt ? (((double)(table->bt->nr_bytes)) / 1024.0) : 0.0;
	sprintf(buffer, "%8lu (%5.2lf%%) %4lu (%.1lfKB) %7u (%.1lfKB)",
		table->volume, vp, table->nr_mi, ik, bt_bytes, bk);
}

void table_show(struct Table *const table, FILE *const fo)
{
	char buffer[1024];
	table_analysis_short(table, buffer);
	fprintf(fo, "%s\n", buffer);
	for (uint64_t i = 0; i < TABLE_NR_BARRELS; i++) {
		barrel_show(&(table->barrels[i]), fo);
	}
}

static struct KeyValue *raw_barrel_lookup(const uint64_t klen0,
					  const uint8_t *const key0,
					  const uint8_t *const raw)
{
	struct RawItem ri;
	if (rawitem_init(&ri, raw) == false) {
		return NULL;
	}

	do {
		if (ri.klen == klen0) {
			const int cmp = memcmp(key0, ri.pk, klen0);
			if (cmp == 0) { // match
				return rawitem_to_keyvalue(&ri);
			}
		}
	} while (true == rawitem_next(&ri));
	return NULL;
}

static bool raw_barrel_fetch(struct MetaTable *const mt,
			     const uint64_t barrel_id, uint8_t *const buf)
{
	const uint64_t off_barrel = (barrel_id * BARREL_ALIGN) + mt->mfh.off;
	const ssize_t r =
		pread(mt->raw_fd, buf, BARREL_ALIGN, (off_t)off_barrel);

	if (mt->stat) {
		__sync_add_and_fetch(&(mt->stat->nr_fetch_barrel), 1);
	}
	return (r == BARREL_ALIGN) ? true : false;
}

static bool raw_barrel_fetch_multiple(struct MetaTable *const mt,
				      const uint64_t start_id,
				      const uint64_t nbarrels,
				      uint8_t *const buf)
{
	const uint64_t off_barrel = (start_id * BARREL_ALIGN) + mt->mfh.off;
	const size_t bytes = BARREL_ALIGN * nbarrels;
	const ssize_t r = pread(mt->raw_fd, buf, bytes, (off_t)off_barrel);
	return (r == BARREL_ALIGN) ? true : false;
}

static const struct MetaIndex *raw_barrel_metaindex(const uint8_t *const buf)
{
	const uint8_t *const pmi = (buf + BARREL_CAP);
	const struct MetaIndex *const mi = (typeof(mi))pmi;
	return mi;
}

static bool raw_barrel_feed_to_tables(
	uint8_t *const raw, struct Table *const *const tables,
	uint64_t (*select_table)(const uint8_t *const, const uint64_t),
	const uint64_t arg2)
{
	struct RawItem ri;
	uint8_t hash[HASHBYTES] __attribute__((aligned(8)));
	const bool r = rawitem_init(&ri, raw);
	if (r == false) {
		return false;
	}
	do {
		SHA1(ri.pk, ri.klen, hash);
		const uint64_t tid = select_table(hash, arg2);
		table_insert_rawitem_mt(tables[tid], &ri, hash);
	} while (rawitem_next(&ri));
	return true;
}

// input -> MetaTable
struct MetaTable *metatable_load(const char *const metafn, const int raw_fd,
				 const bool load_bf, struct Stat *const stat)
{
	FILE *fi = fopen(metafn, "rb");
	if (fi == NULL) {
		return NULL;
	}

	// load header
	struct MetaTable *const mt = (typeof(mt))malloc(sizeof(*mt));
	bzero(mt, sizeof(*mt));
	assert(mt);
	const size_t nh = fread(&(mt->mfh), sizeof(mt->mfh), 1, fi);
	assert(nh == 1);
	// load overflowner metadata
	const uint64_t nr_mi = mt->mfh.nr_mi;
	assert(nr_mi <= TABLE_NR_BARRELS);
	if (nr_mi) {
		struct MetaIndex *const mis =
			(typeof(mis))malloc(sizeof(*mis) * nr_mi);
		assert(mis);
		const size_t nr_read = fread(mis, sizeof(mis[0]), nr_mi, fi);
		assert(nr_mi == nr_read);
		mt->mis = mis;
	}

	// load bloom-filter
	if (load_bf) {
		struct BloomTable *const bt = bloomtable_load(fi);
		assert(bt);
		mt->bt = bt;
	} else {
		mt->bt = NULL;
	}

	// set raw_fd
	mt->raw_fd = raw_fd;
	mt->stat = stat;
	fclose(fi);
	return mt;
}

static struct KeyValue *
metatable_recursive_lookup(struct MetaTable *const mt, const uint16_t bid,
			   uint8_t *const buf, const uint16_t klen,
			   const uint8_t *const key, const uint8_t *const hash)
{
	assert(bid < TABLE_NR_BARRELS);
	const uint32_t hash32 = __hash_order(hash, bid);

	const struct MetaIndex *const mi0 =
		__find_metaindex(mt->mfh.nr_mi, mt->mis, bid);
	const bool fetch0 = (mi0 == NULL) || (hash32 >= mi0->min);
	if (fetch0) {
		const bool rf = raw_barrel_fetch(mt, bid, buf);
		assert(rf);
	}
	const struct MetaIndex *const mi = mi0 ? mi0 :
						 raw_barrel_metaindex(buf);
	if (hash32 < mi->min) { // mast be in another barrel
		assert(mi->id != mi->rid);
		return metatable_recursive_lookup(mt, mi->rid, buf, klen, key,
						  hash);
	}

	if (fetch0 == false) {
		const bool rf = raw_barrel_fetch(mt, bid, buf);
		assert(rf);
	}
	struct KeyValue *const kv = raw_barrel_lookup(klen, key, buf);
	if ((kv == NULL) && (hash32 == mi->min) &&
	    (mi->id != mi->rid)) { // maybe in another barrel
		return metatable_recursive_lookup(mt, mi->rid, buf, klen, key,
						  hash);
	} else { // must in current barrel
		return kv;
	}
}

struct KeyValue *metatable_lookup(struct MetaTable *const mt,
				  const uint16_t klen, const uint8_t *const key,
				  const uint8_t *const hash)
{
	// 桶 id
	const uint16_t bid = table_select_barrel(hash);
	if (mt->bt) {
		// 布隆表存在

		const uint64_t hv = __hash_bf(hash);
		const bool exist = bloomtable_match(mt->bt, bid, hv);
		if (exist == false) {
			if (mt->stat) {
				__sync_add_and_fetch(
					&(mt->stat->nr_true_negative), 1);
			}
			return NULL;
		}
	}
	uint8_t *buf = aligned_alloc(BARREL_ALIGN, BARREL_ALIGN);
	struct KeyValue *const kv =
		metatable_recursive_lookup(mt, bid, buf, klen, key, hash);
	free(buf);
	if (mt->stat) {
		if (kv) {
			__sync_add_and_fetch(&(mt->stat->nr_true_positive), 1);
		} else {
			__sync_add_and_fetch(&(mt->stat->nr_false_positive), 1);
		}
	}
	return kv;
}

void metatable_free(struct MetaTable *const mt)
{
	if (mt->bt) {
		bloomtable_free(mt->bt);
	}
	if (mt->mis) {
		free(mt->mis);
	}
	free(mt);
}

bool metatable_feed_barrels_to_tables(
	struct MetaTable *const mt, const uint16_t start, const uint16_t nr,
	uint8_t *const arena, struct Table *const *const tables,
	uint64_t (*select_table)(const uint8_t *const, const uint64_t),
	const uint64_t arg2)
{
	assert((start + nr) <= TABLE_NR_BARRELS);
	raw_barrel_fetch_multiple(mt, start, nr, arena);
	for (uint64_t i = 0; i < nr; i++) {
		uint8_t *const raw = &(arena[i * BARREL_ALIGN]);
		const bool rf = raw_barrel_feed_to_tables(raw, tables,
							  select_table, arg2);
		assert(rf);
	}
	return true;
}
