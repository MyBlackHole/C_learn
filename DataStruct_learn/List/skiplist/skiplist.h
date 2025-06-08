/*
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef _SKIPLIST_H
#define _SKIPLIST_H

// 双向链表节点
struct sk_link {
	struct sk_link *prev, *next;
};

// 双向链表初始化
static inline void list_init(struct sk_link *link)
{
	link->prev = link;
	link->next = link;
}

// 给双向链表添加节点
static inline void __list_add(struct sk_link *link, struct sk_link *prev,
			      struct sk_link *next)
{
	link->next = next;
	link->prev = prev;
	next->prev = link;
	prev->next = link;
}

// 双向链表节点删除
static inline void __list_del(struct sk_link *prev, struct sk_link *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_add(struct sk_link *link, struct sk_link *prev)
{
	__list_add(link, prev, prev->next);
}

static inline void list_del(struct sk_link *link)
{
	__list_del(link->prev, link->next);
	// 恢复为空状态
	list_init(link);
}

// 判断链表是否为空
static inline int list_empty(struct sk_link *link)
{
	return link->next == link;
}

// 获取 ptr 所在实体
// ptr 与 member 是同一个 type 结构体内同一属性(结构体分配内存中相同偏移量)
// ptr 指针地址减地址为 0 type 结构体 member 属性地址就是 member 偏移量
#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr) - (size_t)(&((type *)0)->member)))

#define skiplist_foreach(pos, end) for (; pos != end; pos = pos->next)

#define skiplist_foreach_safe(pos, n, end) \
	for (n = pos->next; pos != end; pos = n, n = pos->next)

#define MAX_LEVEL 32 /* Should be enough for 2^32 elements */

// 跳表
struct skiplist {
	// 层
	int level;
	// 跳表 node 数量
	int count;
	// 每层双向链表
	struct sk_link head[MAX_LEVEL];
};

// 跳表节点
struct skipnode {
	int key;
	int value;
	struct sk_link link[0];
};

// 创建节点
static struct skipnode *skipnode_new(int level, int key, int value)
{
	struct skipnode *node;
	// node 空间占用加上 level 个 sk_link 空间
	node = malloc(sizeof(*node) + level * sizeof(struct sk_link));
	if (node != NULL) {
		node->key = key;
		node->value = value;
	}
	return node;
}

// 释放跳表节点内存
static void skipnode_delete(struct skipnode *node)
{
	free(node);
}

// 创建跳表
static struct skiplist *skiplist_new(void)
{
	int i;
	// 分配内存
	struct skiplist *list = malloc(sizeof(*list));
	// 初始化
	if (list != NULL) {
		list->level = 1;
		list->count = 0;
		// 初始化每一个双向链表
		for (i = 0; i < (sizeof(list->head) / sizeof(list->head[0]));
		     i++) {
			list_init(&list->head[i]);
		}
	} else {
		perror("malloc(sizeof(*list)) error");
		exit(1);
	}
	return list;
}

// 释放跳表
static void skiplist_delete(struct skiplist *list)
{
	struct sk_link *n;
	// 第 0 层链表包含所有节点
	struct sk_link *pos = list->head[0].next;
	skiplist_foreach_safe(pos, n, &list->head[0])
	{
		struct skipnode *node =
			list_entry(pos, struct skipnode, link[0]);
		skipnode_delete(node);
	}
	free(list);
}

// 随机层数
static int random_level(void)
{
	int level = 1;
	const double p = 0.25;
	while ((random() & 0xffff) < 0xffff * p) {
		level++;
	}
	return level > MAX_LEVEL ? MAX_LEVEL : level;
}

// key查找
/*
 * 查询 3 慢, 增加 skiplist_foreach 遍历完一层都没有小于的，
 * 则 end = end->prev; pos = pos
 * 1
 * 1 2
 * 1 2 3
 */
static struct skipnode *skiplist_search(struct skiplist *list, int key)
{
	struct skipnode *node;
	int i = list->level - 1;
	struct sk_link *pos = &list->head[i];
	struct sk_link *end = &list->head[i];

	// 遍历每一层
	for (; i >= 0; i--) {
		pos = pos->next;
		skiplist_foreach(pos, end)
		{
			node = list_entry(pos, struct skipnode, link[i]);
			if (node->key >= key) {
				end = &node->link[i];
				break;
			}
		}
		if (node->key == key) {
			// 找到提前返回
			return node;
		}
		pos = end->prev;
		pos--;
		end--;
	}

	return NULL;
}

// 给跳表添加元素
static struct skipnode *skiplist_insert(struct skiplist *list, int key,
					int value)
{
	// 获取一个层数
	int level = random_level();
	if (level > list->level) {
		list->level = level;
	}

	// 创建跳表节点
	struct skipnode *node = skipnode_new(level, key, value);
	if (node != NULL) {
		// 当前跳表层数
		int i = list->level - 1;
		struct sk_link *pos = &list->head[i];
		struct sk_link *end = &list->head[i];

		// 遍历每一层
		for (; i >= 0; i--) {
			pos = pos->next;

			// 遍历链表
			skiplist_foreach(pos, end)
			{
				// pos 不等于 end 时

				// 根据 pos 获取对应的跳表节点
				struct skipnode *nd = list_entry(
					pos, struct skipnode, link[i]);
				if (nd->key >= key) {
					// 当 nd->key 大于 key
					// 时，把遍历结束节点改为当前节点相同层链表节点
					end = &nd->link[i];
					// 退出 skiplist_foreach 循环
					break;
				}
			}

			pos = end->prev;
			if (i < level) {
				// 满足随机层高度则添加
				// 添加节点
				__list_add(&node->link[i], pos, end);
			}

			// 切换到下一层
			// pos-- 对应节点是小于等于 key
			// end-- 对应节点是大于等于 key
			pos--;
			end--;
		}

		// 添加成功加一
		list->count++;
	}
	return node;
}

// 删除节点、层高维护
static void __remove(struct skiplist *list, struct skipnode *node, int level)
{
	int i;
	for (i = 0; i < level; i++) {
		// 删除链表节点
		list_del(&node->link[i]);
		if (list_empty(&list->head[i])) {
			// 当前层列表为空,层减一
			list->level--;
		}
	}
	// 释放内存
	skipnode_delete(node);
	// 数量减一
	list->count--;
}

// 跳表元素删除
static void skiplist_remove(struct skiplist *list, int key)
{
	struct sk_link *n;
	struct skipnode *node;
	int i = list->level - 1;
	struct sk_link *pos = &list->head[i];
	struct sk_link *end = &list->head[i];

	// 遍历每层
	for (; i >= 0; i--) {
		pos = pos->next;
		// 遍历链表
		skiplist_foreach_safe(pos, n, end)
		{
			node = list_entry(pos, struct skipnode, link[i]);
			if (node->key > key) {
				end = &node->link[i];
				break;
			} else if (node->key == key) {
				/* we allow nodes with same key. */
				// 这里删除结束没有退出，是因为允许相同 key 插入
				__remove(list, node, i + 1);
			}
		}
		pos = end->prev;
		pos--;
		end--;
	}
}

// 打印整个跳表
static void skiplist_dump(struct skiplist *list)
{
	struct skipnode *node;
	int i = list->level - 1;
	struct sk_link *pos = &list->head[i];
	struct sk_link *end = &list->head[i];

	printf("\nTotal %d nodes: \n", list->count);
	// 遍历每一层
	for (; i >= 0; i--) {
		// 切换到下一个节点
		pos = pos->next;
		printf("level %d:\n", i + 1);
		// 遍历列表
		skiplist_foreach(pos, end)
		{
			node = list_entry(pos, struct skipnode, link[i]);
			printf("key:0x%08x value:0x%08x\n", node->key,
			       node->value);
		}
		pos = &list->head[i];
		pos--;
		end--;
	}
}

#endif /* _SKIPLIST_H */
