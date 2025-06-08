#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listhash.h"

#ifdef MEMORY_TEST
#include <mcheck.h>
#endif

void hash_tab_dump(hash_tab *h)
{
	int i = 0;
	hash_tab_node *cur = NULL;

	if (h == NULL) {
		return;
	}

	printf("\r\n----开始--size[%d],nel[%d]------------", h->size, h->nel);
	for (i = 0; i < h->size; i++) {
		printf("\r\n htables[%d]:", i);
		cur = h->htables[i];
		while ((cur != NULL)) {
			printf("key[%s],data[%s] ", (char *)cur->key,
			       (char *)cur->data);
			cur = cur->next;
		}
	}

	printf("\r\n----结束--size[%d],nel[%d]------------", h->size, h->nel);
}

/**
 * 缓存
 */
struct test_node {
	char key[80];
	char data[80];
};

void hash_tab_node_free(hash_tab_node *node)
{
	struct test_node *ptmp = NULL;

	ptmp = container(node->key, struct test_node, key);

	free(ptmp);
	free(node);
}
/**
 * @def 对字符进行hash计算
 * @param str:key
 * @return key
 */
unsigned int siample_hash(const char *str)
{
	register unsigned int hash = 0;
	register unsigned int seed = 131;

	while (*str) {
		hash = hash * seed + *str++;
	}

	return hash & (0x7FFFFFFF);
}

/**
 * @def 桶选择
 * @param h:hash表
 * @param key:key
 * @return int
 */
int hash_tab_hvalue(hash_tab *h, const void *key)
{
	return (siample_hash(key) % h->size);
}

/**
 * @def key比较
 * @param h:hash表
 * @param key1:key
 * @param key2:key
 * @return int
 */
int hash_tab_keycmp(hash_tab *h, const void *key1, const void *key2)
{
	return strcmp(key1, key2);
}

int main()
{
	int i = 0;
	int res = 0;
	char *pres = NULL;

	// hash节点指针声明
	hash_tab_node *node = NULL;
	struct test_node *p = NULL;

	// hashtab指针声明
	hash_tab *h = NULL;

#ifdef MEMORY_TEST
	setenv("MALLOC_TRACE", "1.txt", 1);
	mtrace();
#endif

	h = hash_tab_create(5, hash_tab_hvalue, hash_tab_keycmp,
			    hash_tab_node_free);
	assert(h != NULL);
	while (1) {
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 和value，当可以等于\"quit\"时退出");
		scanf("%s", p->key);
		scanf("%s", p->data);

		if (strcmp(p->key, "quit") == 0) {
			free(p);
			break;
		}

		res = hash_tab_insert(h, p->key, p->data);
		if (res != 0) {
			free(p);
			printf("\r\n key[%s],data[%s] insert failed %d", p->key,
			       p->data, res);
		} else {
			printf("\r\n key[%s],data[%s] insert success %d",
			       p->key, p->data, res);
		}
	}

	hash_tab_dump(h);

	while (1) {
		p = (struct test_node *)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 查询value的数值，当可以等于\"quit\"时退出");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0) {
			free(p);
			break;
		}
		pres = hash_tab_search(h, p->key);
		if (pres == NULL) {
			printf("\r\n key[%s] search data failed", p->key);
		} else {
			printf("\r\n key[%s],search data[%s] success", p->key,
			       pres);
		}
		free(p);
	}
	hash_tab_dump(h);
	while (1) {
		p = (struct test_node *)malloc(sizeof(struct test_node));
		/**
         * 断言
         */
		assert(p != NULL);
		printf("\r\n 请输入key 删除节点的数值，当可以等于\"quit\"时退出");
		scanf("%s", p->key);

		if (strcmp(p->key, "quit") == 0) {
			free(p);
			break;
		}
		node = hash_tab_delete(h, p->key);
		if (node == NULL) {
			printf("\r\n key[%s] delete node failed ", p->key);
		} else {
			printf("\r\n key[%s],delete data[%s] success",
			       (char *)node->key, (char *)node->data);
			h->hash_node_free(node);
		}
		free(p);
		hash_tab_dump(h);
	}

	hash_tab_destory(h);
#ifdef MEMORY_TEST
	muntrace();
#endif
	return 0;
}
