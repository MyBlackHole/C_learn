#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEGREE 3
typedef int KEY_VALUE;

typedef struct _btree_node {
	KEY_VALUE *keys;
	struct _btree_node **childrens;
	int num;
	int leaf;
} btree_node;

typedef struct _btree {
	btree_node *root;
	int size;
} btree;

btree_node *btree_create_node(int size, int leaf)
{
	btree_node *node = (btree_node *)calloc(1, sizeof(btree_node));
	if (node == NULL) {
		assert(0);
	}

	node->leaf = leaf;
	node->keys = (KEY_VALUE *)calloc(1, (2 * size - 1) * sizeof(KEY_VALUE));
	node->childrens =
		(btree_node **)calloc(1, (2 * size) * sizeof(btree_node));
	node->num = 0;

	return node;
}

void btree_destroy_node(btree_node *node)
{
	assert(node);

	free(node->childrens);
	free(node->keys);
	free(node);
}

void btree_create(btree *btree, int size)
{
	btree->size = size;

	btree_node *node_p = btree_create_node(size, 1);
	btree->root = node_p;
}

void btree_split_child(btree *btree, btree_node *node, int idx)
{
	int size = btree->size;

	btree_node *node_y = node->childrens[idx];
	btree_node *node_z = btree_create_node(size, node_y->leaf);

	node_z->num = size - 1;

	int index = 0;
	for (index = 0; index < size - 1; index++) {
		node_z->keys[index] = node_y->keys[index + size];
	}
	if (node_y->leaf == 0) {
		for (index = 0; index < size; index++) {
			node_z->childrens[index] =
				node_y->childrens[index + size];
		}
	}

	node_y->num = size - 1;
	for (index = node->num; index >= idx + 1; index--) {
		node->childrens[index + 1] = node->childrens[index];
	}

	node->childrens[idx + 1] = node_z;

	for (index = node->num - 1; index >= idx; index--) {
		node->keys[index + 1] = node->keys[index];
	}
	node->keys[idx] = node_y->keys[size - 1];
	node->num += 1;
}

void btree_insert_nonfull(btree *btree, btree_node *node, KEY_VALUE key)
{
	int index = node->num - 1;

	if (node->leaf == 1) {
		while (index >= 0 && node->keys[index] > key) {
			node->keys[index + 1] = node->keys[index];
			index--;
		}
		node->keys[index + 1] = key;
		node->num += 1;
	} else {
		while (index >= 0 && node->keys[index] > key)
			index--;

		if (node->childrens[index + 1]->num ==
		    (2 * (btree->size)) - 1) {
			btree_split_child(btree, node, index + 1);
			if (key > node->keys[index + 1]) {
				index++;
			}
		}

		btree_insert_nonfull(btree, node->childrens[index + 1], key);
	}
}

void btree_insert(btree *btree, KEY_VALUE key)
{
	// int t = T->t;

	btree_node *node = btree->root;
	if (node->num == 2 * btree->size - 1) {
		btree_node *node = btree_create_node(btree->size, 0);
		btree->root = node;

		node->childrens[0] = node;

		btree_split_child(btree, node, 0);

		int index = 0;
		if (node->keys[0] < key) {
			index++;
		}
		btree_insert_nonfull(btree, node->childrens[index], key);
	} else {
		btree_insert_nonfull(btree, node, key);
	}
}

void btree_traverse(btree_node *node)
{
	int index = 0;

	for (index = 0; index < node->num; index++) {
		if (node->leaf == 0) {
			btree_traverse(node->childrens[index]);
		}
		printf("%C ", node->keys[index]);
	}

	if (node->leaf == 0) {
		btree_traverse(node->childrens[index]);
	}
}

void btree_print(btree *btree, btree_node *node, int layer)
{
	btree_node *node_p = node;
	int index;
	if (node_p) {
		printf("\nlayer = %d keynum = %d is_leaf = %d\n", layer,
		       node_p->num, node_p->leaf);
		for (index = 0; index < node->num; index++) {
			printf("%c ", node_p->keys[index]);
		}
		printf("\n");
#if 0
		printf("%p\n", p);
		for(i = 0; i <= 2 * T->t; i++)
			printf("%p ", p->childrens[i]);
		printf("\n");
#endif
		layer++;
		for (index = 0; index <= node_p->num; index++) {
			if (node_p->childrens[index]) {
				btree_print(btree, node_p->childrens[index],
					    layer);
			}
		}
	}

	else {
		printf("the tree is empty\n");
	}
}

int btree_bin_search(btree_node *node, int low, int high, KEY_VALUE key)
{
	int mid;
	if (low > high || low < 0 || high < 0) {
		return -1;
	}

	while (low <= high) {
		mid = (low + high) / 2;
		if (key > node->keys[mid]) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return low;
}

//{child[idx], key[idx], child[idx+1]}
void btree_merge(btree *btree, btree_node *node, int idx)
{
	btree_node *left = node->childrens[idx];
	btree_node *right = node->childrens[idx + 1];

	int index = 0;

	/////data merge
	left->keys[btree->size - 1] = node->keys[idx];
	for (index = 0; index < btree->size - 1; index++) {
		left->keys[btree->size + index] = right->keys[index];
	}
	if (!left->leaf) {
		for (index = 0; index < btree->size; index++) {
			left->childrens[btree->size + index] =
				right->childrens[index];
		}
	}
	left->num += btree->size;

	// destroy right
	btree_destroy_node(right);

	// node
	for (index = idx + 1; index < node->num; index++) {
		node->keys[index - 1] = node->keys[index];
		node->childrens[index] = node->childrens[index + 1];
	}
	node->childrens[index + 1] = NULL;
	node->num -= 1;

	if (node->num == 0) {
		btree->root = left;
		btree_destroy_node(node);
	}
}

void btree_delete_key(btree *btree, btree_node *node, KEY_VALUE key)
{
	if (node == NULL) {
		return;
	}

	int idx = 0, index;

	while (idx < node->num && key > node->keys[idx]) {
		idx++;
	}

	if (idx < node->num && key == node->keys[idx]) {
		if (node->leaf) {
			for (index = idx; index < node->num - 1; index++) {
				node->keys[index] = node->keys[index + 1];
			}

			node->keys[node->num - 1] = 0;
			node->num--;

			if (node->num == 0) { // root
				free(node);
				btree->root = NULL;
			}

			return;
		} else if (node->childrens[idx]->num >= btree->size) {
			btree_node *left = node->childrens[idx];
			node->keys[idx] = left->keys[left->num - 1];

			btree_delete_key(btree, left,
					 left->keys[left->num - 1]);
		} else if (node->childrens[idx + 1]->num >= btree->size) {
			btree_node *right = node->childrens[idx + 1];
			node->keys[idx] = right->keys[0];

			btree_delete_key(btree, right, right->keys[0]);
		} else {
			btree_merge(btree, node, idx);
			btree_delete_key(btree, node->childrens[idx], key);
		}
	} else {
		btree_node *child = node->childrens[idx];
		if (child == NULL) {
			printf("Cannot del key = %d\n", key);
			return;
		}

		if (child->num == btree->size - 1) {
			btree_node *left = NULL;
			btree_node *right = NULL;
			if (idx - 1 >= 0) {
				left = node->childrens[idx - 1];
			}
			if (idx + 1 <= node->num) {
				right = node->childrens[idx + 1];
			}

			if ((left && left->num >= btree->size) ||
			    (right && right->num >= btree->size)) {
				int rich_r = 0;
				if (right) {
					rich_r = 1;
				}
				if (left && right) {
					rich_r = (right->num > left->num) ? 1 :
									    0;
				}

				if (right && right->num >= btree->size &&
				    rich_r) { // borrow from next
					child->keys[child->num] =
						node->keys[idx];
					child->childrens[child->num + 1] =
						right->childrens[0];
					child->num++;

					node->keys[idx] = right->keys[0];
					for (index = 0; index < right->num - 1;
					     index++) {
						right->keys[index] =
							right->keys[index + 1];
						right->childrens[index] =
							right->childrens[index +
									 1];
					}

					right->keys[right->num - 1] = 0;
					right->childrens[right->num - 1] =
						right->childrens[right->num];
					right->childrens[right->num] = NULL;
					right->num--;
				} else { // borrow from prev

					for (index = child->num; index > 0;
					     index--) {
						child->keys[index] =
							child->keys[index - 1];
						child->childrens[index + 1] =
							child->childrens[index];
					}

					child->childrens[1] =
						child->childrens[0];
					child->childrens[0] =
						left->childrens[left->num];
					child->keys[0] = node->keys[idx - 1];

					child->num++;

					node->keys[idx - 1] =
						left->keys[left->num - 1];
					left->keys[left->num - 1] = 0;
					left->childrens[left->num] = NULL;
					left->num--;
				}
			} else if ((!left || (left->num == btree->size - 1)) &&
				   (!right ||
				    (right->num == btree->size - 1))) {
				if (left && left->num == btree->size - 1) {
					btree_merge(btree, node, idx - 1);
					child = left;
				} else if (right &&
					   right->num == btree->size - 1) {
					btree_merge(btree, node, idx);
				}
			}
		}

		btree_delete_key(btree, child, key);
	}
}

int btree_delete(btree *btree, KEY_VALUE key)
{
	if (!btree->root) {
		return -1;
	}

	btree_delete_key(btree, btree->root, key);
	return 0;
}

int main()
{
	btree btree = { 0 };

	btree_create(&btree, 3);
	srand(48);

	int index = 0;
	char key[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (index = 0; index < 26; index++) {
		// key[i] = rand() % 1000;
		printf("%c ", key[index]);
		btree_insert(&btree, key[index]);
	}

	btree_print(&btree, btree.root, 0);

	for (index = 0; index < 26; index++) {
		printf("\n---------------------------------\n");
		btree_delete(&btree, key[25 - index]);
		// btree_traverse(T.root);
		btree_print(&btree, btree.root, 0);
	}
}
