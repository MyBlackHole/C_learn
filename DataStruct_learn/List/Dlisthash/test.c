#include <assert.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dlist.h"
#include "LinkedHashMap.h"

struct test_node {
	char key[80];
	char data[80];
};

// 局部敏感哈希
unsigned int siample_hash(const char *str)
{
	register unsigned int hash = 0;
	register unsigned int seed = 131;

	while (*str) {
		hash = hash * seed + *str++;
	}
	// 0x7FFFFFFF 是 31 位 1
	return hash & (0x7FFFFFFF);
}

// index 计算
int hashtab_hvalue(LinkedHashMap *h, const void *key)
{
	return (siample_hash(key) % h->size);
}

// 比较计算
int hashtab_keycmp(LinkedHashMap *h, const void *key1, const void *key2)
{
	return strcmp(key1, key2);
}

// 节点数据释放
void hashtab_node_free(LiskedHashMapNode *node, int flg)
{
	struct test_node *ptmp = NULL;

	ptmp = list_entry(node->key, struct test_node, key);

	free(ptmp);
	if (flg) {
		free(node);
	}
}

int main()
{
	// int i = 0;
	int res = 0;
	char *pres = NULL;
	LiskedHashMapNode *node = NULL;
	struct test_node *p = NULL;
	LinkedHashMap *h = NULL;

	// 通过对内存管理系列函数(malloc，realloc，memalign，free)注册钩子来达到监控内存泄露和其他内存错误操作
	setenv("MALLOC_TRACE", "1.txt", 1);
	mtrace();

	// 创建 hash
	h = LinkedHashMap_Create(3, 6, hashtab_hvalue, hashtab_keycmp,
				 hashtab_node_free);
	assert(h != NULL);

	// 插入
	while (1) {
		// 分配创建一个 test_node 节点
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 和value，当可以等于\"quit\"时退出");
		scanf("%s", p->key);
		scanf("%s", p->data);

		// 退出判定
		if (strcmp(p->key, "quit") == 0) {
			free(p);
			break;
		}

		res = LinkedHashMap_insert(h, p->key, p->data);
		if (res != 0) {
			free(p);
			printf("\r\n key[%s],data[%s] insert failed %d", p->key,
			       p->data, res);
		} else {
			printf("\r\n key[%s],data[%s] insert success %d",
			       p->key, p->data, res);
		}
		LinkedHashMap__dump(h);
	}

	// 查询
	while (1) {
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 查询value的数值，当可以等于\"quit\"时退出");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0) {
			free(p);
			break;
		}
		pres = LinkedHashMap_search(h, p->key);
		if (pres == NULL) {
			printf("\r\n key[%s] search data failed", p->key);
		} else {
			printf("\r\n key[%s],search data[%s] success", p->key,
			       pres);
		}
		free(p);
		LinkedHashMap__dump(h);
	}

	// 删除
	while (1) {
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 删除节点的数值，当可以等于\"quit\"时退出");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0) {
			free(p);
			break;
		}
		node = LinkedHashMap_delete(h, p->key);
		if (node == NULL) {
			printf("\r\n key[%s] delete node failed ", p->key);
		} else {
			printf("\r\n key[%s],delete data[%s] success",
			       (char *)node->key, (char *)node->data);
			h->hash_node_free(node, 1);
		}
		free(p);
		LinkedHashMap__dump(h);
	}

	LinkedHashMap_destory(h);
	muntrace();
	return 0;
}
