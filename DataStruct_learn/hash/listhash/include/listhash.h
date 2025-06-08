/**
 * linux-4.19.1\security\selinux\ss\hashtab.c
 * linux-4.19.1\security\selinux\ss\hashtab.h
 */

#ifndef __HASHTAB_H__
#define __HASHTAB_H__

typedef struct _hashtab_node {
	void *key;
	void *data;
	struct _hashtab_node *next;
} hash_tab_node;

typedef struct _hashtab {
	/*哈希桶*/
	hash_tab_node **htables;

	/*哈希桶的最大数量*/
	int size;

	/*哈希桶中元素的个数*/
	int nel;

	/*哈希函数*/
	int (*hash_value)(struct _hashtab *h, const void *key);

	/*哈希key比较函数，当哈希数值一致时使用*/
	int (*keycmp)(struct _hashtab *h, const void *key1, const void *key2);
	void (*hash_node_free)(hash_tab_node *node);
} hash_tab;

#define HASHTAB_MAX_NODES (0xffffffff)

/*哈希函数*/
typedef int (*hash_key_func)(struct _hashtab *h, const void *key);

/*哈希key比较函数，当哈希数值一致时使用*/
typedef int (*keycmp_func)(struct _hashtab *h, const void *key1,
			   const void *key2);
typedef void (*hash_node_free_func)(hash_tab_node *node);

/*根据当前结构体元素的地址，获取到结构体首地址*/
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
#define container(ptr, type, member)                               \
	({                                                         \
		const typeof(((type *)0)->member) *__mptr = (ptr); \
		(type *)((char *)__mptr - offsetof(type, member)); \
	})

hash_tab *hash_tab_create(int size, hash_key_func hash_value,
			  keycmp_func key_cmp,
			  hash_node_free_func hash_node_free);

void hash_tab_destory(hash_tab *h);

int hash_tab_insert(hash_tab *h, void *key, void *data);

hash_tab_node *hash_tab_delete(hash_tab *h, void *key);

void *hash_tab_search(hash_tab *h, void *key);

#endif
