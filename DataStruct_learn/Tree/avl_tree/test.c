#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

int main()
{
	int choice;
	int flag = 1;
	int insert_num;
	int query_num;

	avlNode *root = NULL;
	avlNode *temp_node;

	while (flag == 1) {
		printf("\n\nEnter the Step to Run : \n");

		printf("\t1: Insert a node into AVL tree\n");
		printf("\t2: Delete a node in AVL tree\n");
		printf("\t3: Search a node into AVL tree\n");
		printf("\t4: printPreOrder (Ro L R) Tree\n");
		printf("\t5: printInOrder (L Ro R) Tree\n");
		printf("\t6: printPostOrder (L R Ro) Tree\n");
		printf("\t7: printAVL Tree\n");

		printf("\t0: EXIT\n");
		scanf("%d", &choice);

		switch (choice) {
		case 0: {
			flag = 0;
			printf("\n\t\tExiting, Thank You !!\n");
			break;
		}

		case 1: {
			printf("\n\tEnter the Number to insert: ");
			scanf("%d", &insert_num);

			temp_node = findNode(root, insert_num);

			if (temp_node != NULL) {
				printf("\n\t %d Already exists in the tree\n",
				       insert_num);
			} else {
				printf("\n\tPrinting AVL Tree\n");
				printAVL(root, 1);
				printf("\n");

				root = insert(root, insert_num);
				printf("\n\tPrinting AVL Tree\n");
				printAVL(root, 1);
				printf("\n");
			}

			break;
		}

		case 2: {
			printf("\n\tEnter the Number to Delete: ");
			scanf("%d", &query_num);

			temp_node = findNode(root, query_num);

			if (temp_node == NULL) {
				printf("\n\t %d Does not exist in the tree\n",
				       query_num);
			} else {
				printf("\n\tPrinting AVL Tree\n");
				printAVL(root, 1);
				printf("\n");
				root = delete (root, query_num);

				printf("\n\tPrinting AVL Tree\n");
				printAVL(root, 1);
				printf("\n");
			}

			break;
		}

		case 3: {
			printf("\n\tEnter the Number to Search: ");
			scanf("%d", &query_num);

			temp_node = findNode(root, query_num);

			if (temp_node == NULL) {
				printf("\n\t %d : Not Found\n", query_num);
			} else {
				printf("\n\t %d : Found at height %d \n",
				       query_num, temp_node->height);

				printf("\n\tPrinting AVL Tree\n");
				printAVL(root, 1);
				printf("\n");
			}

			break;
		}

		case 4: {
			printf("\nPrinting Tree preOrder\n");
			printPreOrder(root);

			break;
		}

		case 5: {
			printf("\nPrinting Tree inOrder\n");
			printInOrder(root);

			break;
		}

		case 6: {
			printf("\nPrinting Tree PostOrder\n");
			printPostOrder(root);

			break;
		}

		case 7: {
			printf("\nPrinting AVL Tree\n");
			printAVL(root, 1);

			break;
		}

		default: {
			flag = 0;
			printf("\n\t\tExiting, Thank You !!\n");
			break;
		}
		}
	}

	return 0;
}
