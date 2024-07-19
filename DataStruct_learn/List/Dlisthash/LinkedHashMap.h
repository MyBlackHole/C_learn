/*************************************************************************
 > File Name: LinkedHashMap.h
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-11-08
 > Desc:
 ************************************************************************/

#ifndef __LINKED_HASH_MAP__
#define __LINKED_HASH_MAP__
#include "Dlist.h"

/*数据存放节点*/
typedef struct _lisked_hash_map_node {
	/*键*/
	void *key;
	/*数据*/
	void *data;
	/*哈希冲突时，用来挂接后续节点*/
	struct _lisked_hash_map_node *next;
	/*用来挂接双向链表*/
	struct list_head Dlist_node;
} LiskedHashMapNode;

typedef struct _lisked_hash_map {
	/*哈希桶*/
	LiskedHashMapNode **hTabs;
	/*双向循环链表头*/
	// 挂上所有数据
	struct list_head header;
	/**/
	int size;
	/*支持最大节点数*/
	int nel_max;
	/*当前节点数*/
	int nel;
	/*哈希函数*/
	int (*hash_value)(struct _lisked_hash_map *h, const void *key);
	/*哈希key比较函数，当哈希数值一致时使用*/
	int (*keycmp)(struct _lisked_hash_map *h, const void *key1,
		      const void *key2);
	/*用来释放节点内存*/
	void (*hash_node_free)(LiskedHashMapNode *node, int flg);
} LinkedHashMap;

/*哈希函数*/
typedef int (*hash_value_func)(struct _lisked_hash_map *h, const void *key);
/*哈希key比较函数，当哈希数值一致时使用*/
typedef int (*keycmp_func)(struct _lisked_hash_map *h, const void *key1,
			   const void *key2);

typedef void (*hash_node_free_func)(LiskedHashMapNode *node, int flg);

LiskedHashMapNode *LinkedHashMap_delete(LinkedHashMap *h, void *key);

/*
 * size 桶数量
 * nel_max 最大节点数量
 *
 */
LinkedHashMap *LinkedHashMap_Create(int size, int nel_max,
				    hash_value_func hash_value,
				    keycmp_func keycmp,
				    hash_node_free_func hash_node_free);

void LinkedHashMap_destory(LinkedHashMap *h);
int LinkedHashMap_insert(LinkedHashMap *h, void *key, void *data);

LiskedHashMapNode *LinkedHashMap_delete(LinkedHashMap *h, void *key);

void *LinkedHashMap_search(LinkedHashMap *h, void *key);
void LinkedHashMap__dump(LinkedHashMap *h);
#endif
