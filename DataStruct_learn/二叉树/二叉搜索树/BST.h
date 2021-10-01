#ifndef __BST_H
#define __BST_H

typedef struct TreeNode
{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} Node;

// 创建二叉搜索树
Node *CreateNode();

// 插入节点
int InserNode(Node *node, int value);

// 删除节点
int DeleteNode(Node *parent, Node *node, int value);

// 节点查找
Node *SearchNode(Node *node, int value);

int FreedTree(Node *node);

#endif __BST_H
