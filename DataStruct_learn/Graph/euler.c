#include <stdbool.h>
#include <stdio.h>

#include "graph.h"

// Return the number of vertices that v is
// connected to
// 获取节点 v 的度数量
int degree(Graph g, int nV, Vertex v)
{
	int deg = 0;
	Vertex w;
	for (w = 0; w < nV; w++)
		if (adjacent(g, v, w))
			deg++;
	return deg;
}

// If start from vertex v, decide if the
// graph has euler path
bool hasEulerPath(Graph g, int nV, Vertex v, Vertex w)
{
	if (v != w) {
		// 判断节点 v 与节点 w 度数量是否是 2 的倍数
		if (degree(g, nV, v) % 2 == 0 || degree(g, nV, w) % 2 == 0)
			return false;
	} else if (degree(g, nV, v) % 2 != 0) {
		return false;
	}
	Vertex x;
	// 其他所有节点都应该是 2 的倍数
	for (x = 0; x < nV; x++)
		if (x != v && x != w && degree(g, nV, x) % 2 != 0)
			return false;
	return true;
}

int main(void)
{
	Edge e;
	int n;

	printf("Enter the number of vertices: ");
	scanf("%d", &n);
	Graph g = newGraph(n);

	Vertex src, dest;
	printf("Enter source node: ");
	scanf("%d", &src);
	printf("Enter destination node: ");
	scanf("%d", &dest);

	printf("Enter an edge (from): ");
	while (scanf("%d", &e.v) == 1) {
		printf("Enter an edge (to): ");
		scanf("%d", &e.w);
		insertEdge(g, e);
		printf("Enter an edge (from): ");
	}
	printf("Finished.\n");

	printf("The graph has ");
	if (hasEulerPath(g, n, src, dest))
		printf("an");
	else
		printf("no");
	printf(" Euler path from %d to %d.\n", src, dest);

	freeGraph(g);
	return 0;
}
