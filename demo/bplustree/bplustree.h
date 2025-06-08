/*
 * Copyright (C) 2017, Leo Ma <begeekmyfriend@gmail.com>
 */

#ifndef _BPLUS_TREE_H
#define _BPLUS_TREE_H
#include <unistd.h>

/* 5 node caches are needed at least for self, left and right sibling, sibling
 * of sibling, parent and node seeking */
#define MIN_CACHE_NUM 5

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr) - (size_t)(&((type *)0)->member)))

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member) list_entry((ptr)->prev, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head)                       \
	for (pos = (head)->next, n = pos->next; pos != (head); \
	     pos = n, n = pos->next)

typedef int key_t;

struct list_head {
	struct list_head *prev, *next;
};

static inline void list_init(struct list_head *link)
{
	link->prev = link;
	link->next = link;
}

static inline void __list_add(struct list_head *link, struct list_head *prev,
			      struct list_head *next)
{
	link->next = next;
	link->prev = prev;
	next->prev = link;
	prev->next = link;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_add(struct list_head *link, struct list_head *prev)
{
	__list_add(link, prev, prev->next);
}

static inline void list_add_tail(struct list_head *link, struct list_head *head)
{
	__list_add(link, head->prev, head);
}

static inline void list_del(struct list_head *link)
{
	__list_del(link->prev, link->next);
	list_init(link);
}

static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

typedef struct bplus_node {
	/* 当前节点的偏移量 */
	off_t self;
	/* 父节点的偏移量 */
	off_t parent;
	/* 前一个兄弟节点的偏移量 */
	off_t prev;
	/* 后一个兄弟节点的偏移量 */
	off_t next;
	/* 节点类型，0表示叶子节点，1表示非叶子节点 */
	int type;
	/* If leaf node, it specifies  count of entries,
	 * if non-leaf node, it specifies count of children(branches) */
	/* 如果是叶节点，则指定条目数；
	 * 如果是非叶节点，则指定子节点（分支）数 */
	int children;
} bplus_node;

/*
struct bplus_non_leaf {
        off_t self;
        off_t parent;
        off_t prev;
        off_t next;
        int type;
        int children;
        key_t key[BPLUS_MAX_ORDER - 1];
        off_t sub_ptr[BPLUS_MAX_ORDER];
};

struct bplus_leaf {
        off_t self;
        off_t parent;
        off_t prev;
        off_t next;
        int type;
        int entries;
        key_t key[BPLUS_MAX_ENTRIES];
        long data[BPLUS_MAX_ENTRIES];
};
*/

typedef struct free_block {
	struct list_head link;
	off_t offset;
} free_block;

struct bplus_tree {
	/* 块缓存区
	 * 缓存 5 个块*/
	char *caches;
	int used[MIN_CACHE_NUM];
	/* 索引存放的文件名 */
	char filename[1024];
	/* 文件描述符 */
	int fd;
	int level;
	/* 根节点的偏移量 */
	off_t root;
	/* 文件大小 */
	off_t file_size;
	/* 空闲块的双向链表 */
	struct list_head free_blocks;
};

void bplus_tree_dump(struct bplus_tree *tree);
long bplus_tree_get(struct bplus_tree *tree, key_t key);
int bplus_tree_put(struct bplus_tree *tree, key_t key, long data);
long bplus_tree_get_range(struct bplus_tree *tree, key_t key1, key_t key2);
struct bplus_tree *bplus_tree_init(char *filename, int block_size);
void bplus_tree_deinit(struct bplus_tree *tree);
int bplus_open(char *filename);
void bplus_close(int fd);

#endif /* _BPLUS_TREE_H */
