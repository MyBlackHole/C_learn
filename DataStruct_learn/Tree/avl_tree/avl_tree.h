struct AVLnode {
	int key;
	struct AVLnode *left;
	struct AVLnode *right;
	int height;
};

typedef struct AVLnode avlNode;

avlNode *newNode(int key);

int nodeHeight(avlNode *node);

int heightDiff(avlNode *node);

/* Returns the node with min key in the left subtree*/
avlNode *minNode(avlNode *node);

void printAVL(avlNode *node, int level);

avlNode *rightRotate(avlNode *z);

avlNode *leftRotate(avlNode *z);

avlNode *LeftRightRotate(avlNode *z);

avlNode *RightLeftRotate(avlNode *z);

avlNode *insert(avlNode *node, int key);

avlNode *delete(avlNode *node, int queryNum);

avlNode *findNode(avlNode *node, int queryNum);

void printPreOrder(avlNode *node);

void printInOrder(avlNode *node);

void printPostOrder(avlNode *node);
