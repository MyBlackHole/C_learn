#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

// Assume max size of graph is 40 nodes
struct queue {
	// // 应该增加这个字段的
	// int count;

	int items[SIZE];
	// 前
	int front;
	// 后
	int rear;
};

// Allocates memory for our queue data structure
struct queue *createQueue()
{
	struct queue *q = malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}

// Inserts item at start of queue
void enqueue(struct queue *q, int value)
{
	// 判断是否越界
	if (q->rear == SIZE - 1) {
		printf("\nQueue is Full!!");
	} else {
		// 首次添加初始化
		if (q->front == -1) {
			q->front = 0;
		}
		q->rear++;
		q->items[q->rear] = value;
	}
}

// Checks for empty queue
// 这个不是这样的
int isEmpty(struct queue *q)
{
	// 是否为空
	if (q->rear == -1) {
		return 1;
	} else {
		return 0;
	}
}

// Returns element at front of queue
// 获取一个元素
int pollQueue(struct queue *q)
{
	return q->items[q->front];
}

// Returns item at front of queue and removes it from queue
int dequeue(struct queue *q)
{
	int item;
	// 判断是否为空
	if (isEmpty(q)) {
		printf("Queue is empty");
		item = -1;
	} else {
		item = q->items[q->front];
		q->front++;
		// 牛 B 重合后恢复成-1
		if (q->front > q->rear) {
			q->front = q->rear = -1;
		}
	}
	return item;
}

// Structure to create a graph node
struct node {
	// 节点值
	int vertex;
	// 下一个节点
	struct node *next;
};

// Graph data structure
struct Graph {
	// 节点数
	int numVertices;
	// 节点连接的节点链表
	struct node **adjLists;
	// 节点访问状态
	int *visited;
};

// Memory for a graph node
struct node *createNode(int v)
{
	struct node *newNode = malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

// Allocates memory for graph data structure, in adjacency list format
struct Graph *createGraph(int vertices)
{
	struct Graph *graph = malloc(sizeof(struct Graph));
	graph->numVertices = vertices;

	graph->adjLists = malloc(vertices * sizeof(struct node *));
	graph->visited = malloc(vertices * sizeof(int));

	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
	}

	return graph;
}

// Adds bidirectional edge to graph
// 给图添加节点(无方向)
void addEdge(struct Graph *graph, int src, int dest)
{
	// 创建节点
	struct node *destNode = createNode(dest);
	// 添加节点 src 到 dest 边
	// 1.将 dest 的下一个节点指向 src 可以指向的边链表
	// 2. 再将 dest 自己赋值给 a[src]
	destNode->next = graph->adjLists[src];
	graph->adjLists[src] = destNode;

	// Add edge from dest to src; comment it out for directed graph
	// 添加节点 dest 到 src 边
	struct node *srcNode = createNode(src);
	srcNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = srcNode;
}

// 广度优先搜索
void bfs(struct Graph *graph, int startVertex)
{
	// 初始化队列
	struct queue *q = createQueue();

	// Add to visited list and put in queue
	// 添加开始节点
	graph->visited[startVertex] = 1;
	enqueue(q, startVertex);
	printf("Breadth first traversal from vertex %d is:\n", startVertex);

	// Iterate while queue not empty
	while (!isEmpty(q)) {
		printf("%d ", pollQueue(q));
		int currentVertex = dequeue(q);

		// 获取 currentVertex 节点连接的节点链表
		struct node *temp = graph->adjLists[currentVertex];
		// Add all unvisited neighbours of current vertex to queue to be printed
		// next
		while (temp) {
			// 获取temp节点边指向的下一个adjVertex节点
			int adjVertex = temp->vertex;
			// Only add if neighbour is unvisited
			// 判断是否访问过
			// 没访问过就添加到队列
			if (graph->visited[adjVertex] == 0) {
				graph->visited[adjVertex] = 1;
				enqueue(q, adjVertex);
			}
			// 获取temp节点链表指向的下一个节点
			temp = temp->next;
		}
	}
}

int main()
{
	// int vertices, edges, source, i, src, dst;
	// printf("Enter the number of vertices\n");
	// scanf("%d", &vertices);
	// struct Graph *graph = createGraph(vertices);
	// printf("Enter the number of edges\n");
	// scanf("%d", &edges);
	// for (i = 0; i < edges; i++) {
	//   printf("Edge %d \nEnter source: ", i + 1);
	//   scanf("%d", &src);
	//   printf("Enter destination: ");
	//   scanf("%d", &dst);
	//   addEdge(graph, src, dst);
	// }
	// printf("Enter source of bfs\n");
	// scanf("%d", &source);
	// bfs(graph, source);

	// Uncomment below part to get a ready-made example
	struct Graph *graph = createGraph(6);
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 1, 4);
	addEdge(graph, 1, 3);
	addEdge(graph, 2, 4);
	addEdge(graph, 3, 4);
	bfs(graph, 0);

	return 0;
}
