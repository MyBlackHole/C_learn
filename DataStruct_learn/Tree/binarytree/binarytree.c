#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Implement binary tree in array */
/* 在数组中实现二叉树 */

#define MAX_TREE_NODES (1 << 8)

struct node {
	int data;
};

struct binary_tree {
	union {
		unsigned long nodes;
		struct node *n[MAX_TREE_NODES];
	};
};

void init_binary_tree(struct binary_tree *tree)
{
	int index;

	for (index = 0; index < MAX_TREE_NODES; index++) {
		tree->n[index] = NULL;
	}
}

struct node *create_node(int data)
{
	struct node *node_p;

	node_p = malloc(sizeof(struct node));

	if (node_p) {
		node_p->data = data;
	}

	return node_p;
}

void fake_a_tree(struct binary_tree *tree)
{
	/* data is in ordered */
	int index, data[10] = { 7, 4, 9, 2, 6, 8, 10, 1, 3, 5 };

	init_binary_tree(tree);

	/* root start at 1 */
	for (index = 0; index < 10; index++) {
		tree->n[index + 1] = create_node(data[index]);
	}

	tree->nodes = 10;
}

void _in_order(struct binary_tree *tree, int index)
{
	if (!tree->n[index]) {
		return;
	}

	/* left child at (index << 1) */
	_in_order(tree, index << 1);

	printf("[%2d]: %4d\n", index, tree->n[index]->data);

	/* right child at (index << 1) + 1 */
	_in_order(tree, (index << 1) + 1);
}

void in_order(struct binary_tree *tree)
{
	_in_order(tree, 1);
}

int main()
{
	struct binary_tree tree;

	fake_a_tree(&tree);
	in_order(&tree);
	return 0;
}
