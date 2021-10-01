#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

Node* CreateNode()
{
	Node *node = NULL;
	node = (Node*)malloc(sizeof(Node));

	if (node == NULL)
	{
		printf("line %d (root == NULL)\n", 12);
	}

	node->left = NULL;
	node->right = NULL;

	return node;
}

int InserNode(Node *node, int value)
{
	if (node == NULL)
	{
		node = CreateNode();
		return 0;
	}

	if (node->data == value)
	{
		printf("node->data == value 节点已存在");
		return -1;
	}

	if (node->data < value)
	{
		if (node->left == NULL)
		{
			node->left = CreateNode();
			return 0;
		}
		return InserNode(node->left, value);
	}

	if (node->data > value)
	{
		if (node->right == NULL) {
			node->right = CreateNode();
			return 0;
		}
		return InserNode(node->right, value);
	}

	return 0;
}

Node *SearchNode(Node *node, int value)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->data == value)
	{
		return node;
	}

	if (node->data > value)
	{
		return SearchNode(node->left, value);
	}

	return SearchNode(node->right, value);
}

void DeletNode(Node *parent, Node *cur, int DelData)
{
	Node *SNode = NULL; //后继节点
	Node *PSNode = NULL;    //后继节点的父节点

	if (DelData > cur->data)
	{
		DeletNode(cur, cur->right, DelData);
	}
	else if (DelData < cur->data)
	{
		DeletNode(cur, cur->left, DelData);
	}
	else if(DelData == cur->data)
	{
		// 待删除节点为叶子节点
		if (cur->left == NULL && cur->right == NULL)
		{
			// 如果该节点是父节点的左子树
			if (parent->left == cur)    
			{
				parent->left = NULL;
			}
			// 如果该节点是父节点的右子树
			else if (parent->right == cur)    
			{
				parent->right = NULL;
			}
		}
		// 待删除节点只有左子树
		else if(cur->left != NULL && cur->right == NULL)    
		{
			if (parent->left == cur)
			{
				 parent->left = cur->left;
			}
			else if (parent->right == cur)
			{
				 parent->right = cur->left;
			}
		}
		// 待删除节点只有右子树
		else if(cur->left == NULL && cur->right != NULL)
		{
			if (parent->left == cur)
			{
				 parent->left = cur->right;
			}
			else if (parent->right == cur)
			{
				 parent->right = cur->right;
			}
		}
		// 待删除节点既有左子树也有右子树
		else if(cur->left != NULL && cur->right != NULL)    
		{
			// 搜索后继节点
			SNode = SearchSuccessorNode(cur->right);
			// 搜索后继节点的父节点
			PSNode = SearchParentofSNode(cur->right, cur->right);

			// 后继节点为待删除节点的右子树（后继节点有右子树和没有右子树的操作相同）
			if (cur->right == SNode)    
			{
				if (parent->left == cur)
				{
					parent->left = SNode;
					SNode->left = cur->left;
				}
				else if (parent->right == cur)
				{
					parent->right = SNode;
					SNode->left = cur->left;
				}
			}
			// 后继节点不为待删除节点的右子树，并且该后继节点没有右子树
			else if (cur->right != SNode && SNode->right == NULL)    
			{
				if (parent->left == cur)
				{
					parent->left = SNode;
					SNode->left = cur->left;
					SNode->right = cur->right;
					PSNode->left = NULL;
				}
				else if (parent->right == cur)
				{
					parent->right = SNode;
					SNode->left = cur->left;
					SNode->right = cur->right;
					PSNode->left = NULL;
				}
			}
			// 后继节点不为待删除节点的右子树，并且该后继节点有右子树
			else if (cur->right != SNode && SNode->right != NULL)
			{
				if (parent->left == cur)
				{
					parent->left = SNode;
					// 后继节点的右子树作为后继节点父节点的左子树
					PSNode->left = SNode->right;
					SNode->left = cur->left;
					SNode->right = cur->right;
				}
				else if (parent->right == cur)
				{
					parent->right = SNode;
					// 后继节点的右子树作为后继节点父节点的左子树
					PSNode->left = SNode->right;
					SNode->left = cur->left;
					SNode->right = cur->right;
				}
			}
		}
		// 释放待删除节点
		free(cur);
	}
}
