#include "hash_set.h"

#include <stdio.h>
#include <stdlib.h>

// hash 初始化
extern hash_set_t *init_hash_set()
{
	// 初始化 hash set 结构体内存
	hash_set_t *set = (hash_set_t *)malloc(sizeof(hash_set_t));
	set->keys = calloc(DEFAULT_HASH_SET_CAPACITY, sizeof(void **));
	set->values = calloc(DEFAULT_HASH_SET_CAPACITY, sizeof(void **));
	set->length = 0;
	set->capacity = DEFAULT_HASH_SET_CAPACITY;

	return set;
}

// 添加元素
unsigned add(hash_set_t *set, void *value)
{
	return put(set, hash(value), value);
}

unsigned put(hash_set_t *set, long long hash, void *value)
{
	if (contains_hash(set, hash)) {
		// 存在一致 hash 则判断是否 value 一致
		if (set->keys[retrieve_index_from_hash(hash, set->capacity)] ==
		    value) {
			return 0;
		}

		// collision
		// 能走到这，代表发生碰撞
		resize(set);

		// 重新添加, 直到没有冲突为止
		return put(set, hash, value);
	}

	// 设置 key 对应 value 地址
	set->keys[retrieve_index_from_hash(hash, set->capacity)] = value;
	// 不分配内存赋值？？？
	set->values[set->length++] = value;

	return 1;
}

// 判断是否存在
int contains(hash_set_t *set, void *value)
{
	return set->keys[retrieve_index_from_hash(hash(value), set->capacity)] ==
			       value ?
		       1 :
		       0;
}

// 判断值是否存在
int contains_hash(hash_set_t *set, long long hash)
{
	return set->keys[retrieve_index_from_hash(hash, set->capacity)] ? 1 : 0;
}

// 删除 value
void delete(hash_set_t *set, void *value)
{
	set->keys[retrieve_index_from_hash(hash(value), set->capacity)] = NULL;
}

// adler_32 hash
// 校验和计算 32 位返回值
long long hash(void *value)
{
	char *str = value;

	int a = 1;
	int b = 0;
	const int MODADLER = 65521;

	for (int i = 0; str[i] != '\0'; i++) {
		a = (a + str[i]) % MODADLER;
		b = (b + a) % MODADLER;
	}

	return (b << 16) | a;
}

// 获取 index
unsigned retrieve_index_from_hash(const long long hash, const unsigned capacity)
{
	return (capacity - 1) & (hash ^ (hash >> 12));
}

void resize(hash_set_t *set)
{
	// 扩展数据内存大小同时置零
	void **keys_resized = calloc((set->capacity <<= 1), sizeof(void **));

	// key 与指向数据指针修改  数据迁移
	for (int i = 0; i < set->length; i++) {
		keys_resized[retrieve_index_from_hash(
			hash(set->values[i]), set->capacity)] = set->values[i];
	}

	// 释放元内存
	free(set->keys);

	set->keys = keys_resized;

	void **new_values =
		(void **)realloc(set->values, set->capacity * sizeof(void **));
	set->values = new_values;
}
