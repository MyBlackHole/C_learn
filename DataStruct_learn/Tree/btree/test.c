#include <stdio.h>

#include "btree.h"

// 测试order序(阶)的B-TREE结构基本操作。
// 查找：search，插入：insert，删除：remove。
// 创建：create，销毁：destory，打印：print。

void test_BTree_search(BTree tree, KeyType key)
{
	int pos = -1;
	BTNode *node = BTree_search(tree, key, &pos);
	if (node) {
		printf("在%s节点（包含 %d 个关键字）中找到关键字 %c，其索引为 %d\n",
		       node->isLeaf ? "叶子" : "非叶子", node->keynum, key,
		       pos);
	} else {
		printf("在树中找不到关键字 %c\n", key);
	}
}

void test_BTree_remove(BTree *tree, KeyType key)
{
	printf("\n移除关键字 %c \n", key);
	BTree_remove(tree, key);
	BTree_print(*tree, 1);
	printf("\n");
}

void test_btree()
{
	KeyType array[] = { 'G', 'G', 'M', 'P', 'X', 'A', 'C', 'D',
			    'E', 'J', 'K', 'N', 'O', 'R', 'S', 'T',
			    'U', 'V', 'Y', 'Z', 'F', 'X' };
	// KeyType array[] = {'A','B','C','D','E','F','G','H','I','J'};
	const int length = sizeof(array) / sizeof(KeyType);
	BTree tree = NULL;
	BTNode *node = NULL;
	int pos = -1;
	KeyType key1 = 'R'; // in the tree.
	KeyType key2 = 'B'; // not in the tree.

	// 创建
	BTree_create(&tree, array, length);

	printf("\n=== 创建 B- 树 ===\n");
	BTree_print(tree, 1);
	printf("\n");

	// 查找
	test_BTree_search(tree, key1);
	printf("\n");
	test_BTree_search(tree, key2);

	// 移除不在B树中的元素
	test_BTree_remove(&tree, key2);
	printf("\n");

	// 插入关键字
	printf("\n插入关键字 %c \n", key2);
	BTree_insert(&tree, key2);
	BTree_print(tree, 1);
	printf("\n");

	test_BTree_search(tree, key2);

	// 移除关键字
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'M';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'E';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'G';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'A';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'D';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'K';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'P';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'J';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'C';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'X';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'O';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'V';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'R';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'U';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'T';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'N';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'S';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'Y';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'F';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);

	key2 = 'Z';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);
	BTree_print(tree, 1);
	// 销毁
	BTree_destroy(&tree);
}

int main()
{
	test_btree();

	return 0;
}
