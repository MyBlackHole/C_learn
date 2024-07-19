#include "listhash.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @def hash_tab初始化
 * @param size:桶的个数
 * @param hash_value:hash函数
 * @param key_cmp:key比较
 * @param hash_node_free:释放内存
 * @return hash_tab指针
 */
hash_tab *hash_tab_create(int size, hash_key_func hash_value,
			  keycmp_func key_cmp,
			  hash_node_free_func hash_node_free)
{
	hash_tab *h = NULL;
	int i = 0;

	if ((size < 0) || (hash_value == NULL) || (key_cmp == NULL)) {
		return NULL;
	}

	h = (hash_tab *)malloc(sizeof(hash_tab));
	if (h == NULL) {
		return NULL;
	}

	/**
     * 申请size份hash_tab_node
     */
	h->htables = (hash_tab_node **)malloc(size * sizeof(hash_tab_node *));
	if (h->htables == NULL) {
		return NULL;
	}

	h->size = size;
	h->nel = 0;
	h->hash_value = hash_value;
	h->keycmp = key_cmp;
	h->hash_node_free = hash_node_free;

	for (i = 0; i < size; i++) {
		h->htables[i] = NULL;
	}

	return h;
}

/**
 * @def 释放桶内存
 * @param h:hash表
 */
void hash_tab_destory(hash_tab *h)
{
	int i = 0;
	hash_tab_node *cur = NULL;
	hash_tab_node *tmp = NULL;

	if (h == NULL) {
		return;
	}

	/**
     * 遍历桶
     */
	for (i = 0; i < h->size; i++) {
		cur = h->htables[i];
		while (cur != NULL) {
			tmp = cur;
			cur = cur->next;
			h->hash_node_free(tmp);
		}
		h->htables[i] = NULL;
	}

	free(h->htables);
	free(h);
	return;
}

/**
 * @def 插入
 * @param h:hash表
 * @param key:key
 * @param data:value
 * @return int
 */
int hash_tab_insert(hash_tab *h, void *key, void *data)
{
	unsigned int hvalue = 0;
	int i = 0;
	hash_tab_node *cur = NULL;
	hash_tab_node *prev = NULL;
	hash_tab_node *newnode = NULL;

	if ((h == NULL) || (key == NULL) || (data == NULL)) {
		return 1;
	}

	/*获取hash 数值*/
	hvalue = h->hash_value(h, key);
	cur = h->htables[hvalue];

	/*hash桶中元素是从小到大排列的，找到要插入的位置*/
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) > 0)) {
		prev = cur;
		cur = cur->next;
	}

	/*如果key和当前key比对一致，直接返回，数据已经存在*/
	if ((cur != NULL) && (h->keycmp(h, key, cur->key) == 0)) {
		return 2;
	}

	newnode = (hash_tab_node *)malloc(sizeof(hash_tab_node));
	if (newnode == NULL) {
		return 3;
	}

	newnode->key = key;
	newnode->data = data;
	if (prev == NULL) {
		newnode->next = h->htables[hvalue];
		h->htables[hvalue] = newnode;
	} else {
		newnode->next = prev->next;
		prev->next = newnode;
	}

	h->nel++;
	return 0;
}

/**
 * @def 删除hash数据节点
 * @param h:hash表
 * @param key:key
 * @return hash_tab_node
 */
hash_tab_node *hash_tab_delete(hash_tab *h, void *key)
{
	int hvalue = 0;
	int i = 0;
	hash_tab_node *cur = NULL;
	hash_tab_node *prev = NULL;

	if ((h == NULL) || (key == NULL)) {
		return NULL;
	}

	/*获取hash 数值*/
	hvalue = h->hash_value(h, key);
	cur = h->htables[hvalue];

	/*hash桶中元素是从小到大排列的，找到要插入的位置*/
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) >= 0)) {
		if (h->keycmp(h, key, cur->key) == 0) {
			if (prev == NULL) {
				h->htables[hvalue] = cur->next;
			} else {
				prev->next = cur->next;
			}
			return cur;
		}
		prev = cur;
		cur = cur->next;
	}

	return NULL;
}

void *hash_tab_search(hash_tab *h, void *key)
{
	int hvalue = 0;
	int i = 0;
	hash_tab_node *cur = NULL;

	if ((h == NULL) || (key == NULL)) {
		return NULL;
	}

	/*获取hash 数值*/
	hvalue = h->hash_value(h, key);
	cur = h->htables[hvalue];

	/*hash桶中元素是从小到大排列的，找到要插入的位置*/
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) >= 0)) {
		if (h->keycmp(h, key, cur->key) == 0) {
			return cur->data;
		}
		cur = cur->next;
	}

	return NULL;
}
