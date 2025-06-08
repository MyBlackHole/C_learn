#ifndef __HASH_SET__
#define __HASH_SET__

// 默认 hash set 容量
#define DEFAULT_HASH_SET_CAPACITY 1 << 10

typedef struct {
	// 最大空间
	unsigned capacity;
	// 使用量
	unsigned length;
	// 数据指针
	void **values;
	// index 占位
	void **keys;
} hash_set_t;

extern hash_set_t *init_hash_set();

extern unsigned add(hash_set_t *set, void *value);

unsigned put(hash_set_t *set, long long hash, void *value);

extern int contains(hash_set_t *set, void *value);

int contains_hash(hash_set_t *set, long long hash);

extern void delete(hash_set_t *set, void *value);

extern long long hash(void *value);

extern unsigned retrieve_index_from_hash(const long long hash,
					 const unsigned capacity);

extern void resize(hash_set_t *set);

#endif
