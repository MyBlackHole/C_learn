#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing edge
struct Edge {
	// src 源， dst 目的， weight 权重
	int src, dst, weight;
};

// Structure for storing a graph
struct Graph {
	// 节点数量
	int vertexNum;
	// 边数量
	int edgeNum;
	struct Edge *edges;
};

// Constructs a graph with V vertices and E edges
// 初始化图
void createGraph(struct Graph *G, int V, int E)
{
	G->vertexNum = V;
	G->edgeNum = E;
	G->edges = (struct Edge *)malloc(E * sizeof(struct Edge));
}

// Adds the given edge to the graph
void addEdge(struct Graph *G, int src, int dst, int weight)
{
	// ind 仅此一份
	static int ind;
	struct Edge newEdge;
	newEdge.src = src;
	newEdge.dst = dst;
	newEdge.weight = weight;
	G->edges[ind++] = newEdge;
}

// Utility function to find minimum distance vertex in mdist
int minDistance(int mdist[], int vset[], int V)
{
	int minVal = INT_MAX, minInd;
	for (int i = 0; i < V; i++) {
		if (vset[i] == 0 && mdist[i] < minVal) {
			minVal = mdist[i];
			minInd = i;
		}
	}

	return minInd;
}

// Utility function to print distances
void print(int dist[], int V)
{
	printf("\nVertex  Distance\n");
	for (int i = 0; i < V; i++) {
		if (dist[i] != INT_MAX) {
			printf("%d\t%d\n", i, dist[i]);
		} else {
			printf("%d\tINF", i);
		}
	}
}

void print1(int dist[], int V)
{
	for (int i = 0; i < V; i++) {
		if (dist[i] != INT_MAX) {
			printf("[%d:%d]\t", i, dist[i]);
		} else {
			printf("[%d:-]\t", i);
		}
	}
	printf("\n");
}

// The main function that finds the shortest path from given source
// to all other vertices using Bellman-Ford.It also detects negative
// weight cycle
void BellmanFord(struct Graph *graph, int src)
{
	int V = graph->vertexNum;
	int E = graph->edgeNum;
	int dist[V];

	// Initialize distances array as INF for all except source
	// Intialize source as zero
	// 初始化距离数组
	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
	}
	// 自己到自己距离是零
	dist[src] = 0;

	// Calculate shortest path distance from source to all edges
	// A path can contain maximum (|V|-1) edges
	// 对每个节点遍历一遍所有边
	for (int i = 0; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edges[j].src;
			int v = graph->edges[j].dst;
			int w = graph->edges[j].weight;

			if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
			}
			print1(dist, V);
		}
	}

	// Iterate inner loop once more to check for negative cycle
	// 检测是否有负权重回路
	// dist 携带了 gsrc 到各点最短距离
	for (int j = 0; j < E; j++) {
		// 起点
		int u = graph->edges[j].src;
		// 目的
		int v = graph->edges[j].dst;
		int w = graph->edges[j].weight;

		// 判断是否存在 gsrc 到 u 最段距离 d[u] 加上 u 到 v 的距离 w 小于
		//              gsrc 到 v 最段距离 d[v]
		// d[u] + w + (-d[v]) < 0 存在负环
		if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
			printf("Graph contains negative weight cycle. Hence, shortest "
			       "distance not guaranteed.");
			return;
		}
	}

	print(dist, V);

	return;
}

// Driver Function
// 贝尔曼-福特算法
// O(|V||E|) |V| 和 |E|分别是节点和边的数量
// |V| {v0, v1, v2, v3}, |E| = {(v0, v1), (v0,v2), (v1, v3), (v3,v2)}
// w(v0, v1) = -1, w(v0,v2) = 3, w(v1, v3) = 3, w(v3,v2) = -1
int main()
{
	int V, E, gsrc;
	int src, dst, weight;
	struct Graph G;
	printf("Enter number of vertices: ");
	scanf("%d", &V);
	printf("Enter number of edges: ");
	scanf("%d", &E);
	createGraph(&G, V, E);

	for (int i = 0; i < E; i++) {
		printf("\nEdge %d \nEnter source: ", i + 1);
		scanf("%d", &src);
		printf("Enter destination: ");
		scanf("%d", &dst);
		printf("Enter weight: ");
		scanf("%d", &weight);
		addEdge(&G, src, dst, weight);
	}
	printf("\nEnter source:");
	scanf("%d", &gsrc);
	BellmanFord(&G, gsrc);

	return 0;
}
