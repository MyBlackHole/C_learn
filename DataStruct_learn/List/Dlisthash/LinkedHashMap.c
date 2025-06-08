/*************************************************************************
 > File Name: LinkedHashMap.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-11-08
 > Desc:
 ************************************************************************/
#include "LinkedHashMap.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dlist.h"

LinkedHashMap *LinkedHashMap_Create(int size, int nel_max,
				    hash_value_func hash_value,
				    keycmp_func keycmp,
				    hash_node_free_func hash_node_free)
{
	int i = 0;
	LinkedHashMap *h = NULL;

	if ((size <= 0) || (hash_value == NULL) || (keycmp == NULL)) {
		return NULL;
	}

	// LinkedHashMap 空间分配
	h = (LinkedHashMap *)malloc(sizeof(LinkedHashMap));

	if (h == NULL) {
		return NULL;
	}

	// 空间初始化
	h->hTabs = (LiskedHashMapNode **)malloc(sizeof(LiskedHashMapNode *) *
						size);
	if (h->hTabs == NULL) {
		return NULL;
	}
	h->size = size;
	h->nel = 0;
	h->nel_max = nel_max;
	h->hash_value = hash_value;
	h->keycmp = keycmp;
	h->hash_node_free = hash_node_free;

	for (i = 0; i < size; i++) {
		h->hTabs[i] = NULL;
	}

	INIT_LIST_HEAD(&(h->header));

	return h;
}

void LinkedHashMap_destory(LinkedHashMap *h)
{
	struct list_head *pos = NULL;
	struct list_head *next = NULL;
	LiskedHashMapNode *ptmp = NULL;

	if (h == NULL) {
		return;
	}

	list_for_each_safe(pos, next, &h->header) {
		ptmp = container_of(pos, LiskedHashMapNode, Dlist_node);
		/*从双向链表中删除*/
		list_del_init(pos);
		if (h->hash_node_free != NULL) {
			h->hash_node_free(ptmp, 1);
		}
	}

	free(h->hTabs);
	free(h);

	return;
}

int LinkedHashMap_insert(LinkedHashMap *h, void *key, void *data)
{
	// int i = 0;
	int hPos = 0;
	// struct list_head *pos = NULL;
	LiskedHashMapNode *cur = NULL;
	LiskedHashMapNode *prev = NULL;

	// 桶 index 计算
	hPos = h->hash_value(h, key);
	cur = h->hTabs[hPos];

	// cur 可能是 NULL 或 与 key 相等的 LiskedHashMapNode
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) != 0)) {
		// 判定是否存在相同的 key
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL) {
		// 不存在相等的节点

		/*链表节点满时，取表头节点，从当前哈希表和双向链表中都删除*/
		if (h->nel_max == h->nel) {
			// 节点满了
			cur = LinkedHashMap_delete(
				h, list_entry(h->header.next, LiskedHashMapNode,
					      Dlist_node)
					   ->key);

			assert(cur != NULL);
			/*释放节点key 和data的内容*/
			h->hash_node_free(cur, 0);
		} else {
			/*链表不满时，创建新的节点*/
			cur = (LiskedHashMapNode *)malloc(
				sizeof(LiskedHashMapNode));
			if (cur == NULL) {
				return 1;
			}
		}
		/*插入到hash桶中*/
		if (prev == NULL) {
			cur->next = h->hTabs[hPos];
			h->hTabs[hPos] = cur;
		} else {
			cur->next = prev->next;
			prev->next = cur;
		}
		h->nel++;
	} else {
		/*从双向链表中删除*/
		list_del_init(&(cur->Dlist_node));
		/*只删除key 和data的内存*/
		h->hash_node_free(cur, 0);
	}

	/*赋值*/
	cur->key = key;
	cur->data = data;

	/*加的双向链表尾部*/
	list_add_tail(&(cur->Dlist_node), &(h->header));

	return 0;
}

// 连表节点删除, 返回找到的节点
LiskedHashMapNode *LinkedHashMap_delete(LinkedHashMap *h, void *key)
{
	int hPos = 0;
	// struct list_head *pos = NULL;
	LiskedHashMapNode *cur = NULL;
	LiskedHashMapNode *prev = NULL;

	/*查找当前节点*/
	hPos = h->hash_value(h, key);
	cur = h->hTabs[hPos];
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) != 0)) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL) {
		// 没找到返回 NULL
		return NULL;
	}

	/*从哈希桶中删除*/
	if (prev == NULL) {
		// 首个 cur 就是
		h->hTabs[hPos] = cur->next;
	} else {
		// 非首个 cur
		prev->next = cur->next;
	}

	/*从双向链表中删除*/
	list_del_init(&(cur->Dlist_node));
	h->nel--;

	return cur;
}

// 节点查询
void *LinkedHashMap_search(LinkedHashMap *h, void *key)
{
	int hPos = 0;
	LiskedHashMapNode *cur = NULL;

	/*查找当前节点*/
	hPos = h->hash_value(h, key);
	cur = h->hTabs[hPos];
	while ((cur != NULL) && (h->keycmp(h, key, cur->key) != 0)) {
		cur = cur->next;
	}

	if (cur == NULL) {
		return NULL;
	}

	/*从双向链表中删除节点，加入尾部*/
	if (h->header.prev != &(cur->Dlist_node)) {
		list_del_init(&(cur->Dlist_node));
		list_add_tail(&(cur->Dlist_node), &(h->header));
	}

	return cur->data;
}

// 数据打印
void LinkedHashMap__dump(LinkedHashMap *h)
{
	int i = 0;
	LiskedHashMapNode *cur = NULL;
	struct list_head *pos = NULL;

	if (h == NULL) {
		return;
	}

	printf("\r\n----开始--size[%d],nel[%d]------------", h->size, h->nel);
	for (i = 0; i < h->size; i++) {
		printf("\r\n htables[%d]:", i);
		cur = h->hTabs[i];
		while ((cur != NULL)) {
			printf("key[%s],data[%s] ", (char *)cur->key,
			       (char *)cur->data);
			cur = cur->next;
		}
	}

	printf("\r\n--------------------------------------------------------\r\n");

	list_for_each(pos, &(h->header)) {
		cur = list_entry(pos, LiskedHashMapNode, Dlist_node);
		printf("key[%s] ", (char *)cur->key);
	}

	printf("\r\n----结束--size[%d],nel[%d]------------", h->size, h->nel);
}
