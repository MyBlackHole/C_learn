#include <stdio.h>
#include <stdlib.h>

// 二叉树结点的定义
typedef struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

TreeNode *create(const int value)
{
	TreeNode *node = malloc(sizeof(TreeNode));
	if (node == NULL) {
		return NULL;
	}
	node->val = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// 给定一个节点和一个目标值，返回以这个节点为根的树中，能凑出几个以该节点为路径开头，和为目标值的路径总数。
int count(TreeNode *node, int sum)
{
	if (node == NULL) {
		return 0;
	}
	return (node->val == sum) + count(node->left, sum - node->val) +
	       count(node->right, sum - node->val);
}

// 给定一个节点和一个目标值，返回以这个节点为根的树中，和为目标值的路径总数。
int pathSum(TreeNode *root, int sum)
{
	if (root == NULL) {
		return 0;
	}
	return count(root, sum) + pathSum(root->left, sum) +
	       pathSum(root->right, sum);
}

void free_node(TreeNode *node)
{
	if (node == NULL) {
		return;
	}
	free_node(node->left);
	free_node(node->right);
	free(node);
}

void free_tree(TreeNode *root)
{
	if (root == NULL) {
		return;
	}
	free_node(root);
}

int main(int argc, char *argv[])
{
	TreeNode *root = create(10);
	root->left = create(5);
	root->right = create(-3);
	root->left->left = create(3);
	root->left->right = create(2);
	root->left->left->left = create(3);
	root->left->left->right = create(-2);
	root->left->right->right = create(1);
	root->right->right = create(11);

	printf("%d\n", pathSum(root, 8));

	free_tree(root);

	return EXIT_SUCCESS;
}
