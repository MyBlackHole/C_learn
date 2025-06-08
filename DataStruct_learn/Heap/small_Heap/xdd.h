typedef int Node;

typedef struct MinHeap {
	/* data */
	Node *array;
	int len;
	int MaxSize;
} MinHeap;

/* 初始化堆 */
MinHeap *InitMinHeap(MinHeap *heap, int size);

/* 判断是否为空 */
int EmptyHeap(MinHeap *heap);

/* 上浮 */
int FixUp(MinHeap *heap);

/* 下浮 */
int FixDown(MinHeap *heap);

/* 插入节点 */
int InsertHeap(MinHeap *heap, Node node);

/* 删除节点 */
Node DeleteHeap(MinHeap *heap);

// /* 查询节点 */
// int SelectHeap(MinHeap *heap, Node node);

/* 清空堆 */
int ClearHeap(MinHeap *heap);
