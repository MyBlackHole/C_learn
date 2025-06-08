// Graph ADT
// Adjacency Matrix Representation
#include "graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphRep {
	// 邻接矩阵
	int **edges; // adjacency matrix
	// 节点数
	int nV; // #vertices
	// 边数
	int nE; // #edges
} GraphRep;

// 创建初始化图
Graph newGraph(int V)
{
	assert(V >= 0);
	int i;

	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = V;
	g->nE = 0;

	// allocate memory for each row
	g->edges = malloc(V * sizeof(int *));
	assert(g->edges != NULL);
	// allocate memory for each column and initialise with 0
	for (i = 0; i < V; i++) {
		// 分配并初始化空间
		g->edges[i] = calloc(V, sizeof(int));
		assert(g->edges[i] != NULL);
	}

	return g;
}

// check if vertex is valid in a graph
// 判断节点是否有效
bool validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// 添加边到图
void insertEdge(Graph g, Edge e)
{
	assert(g != NULL && validV(g, e.v) && validV(g, e.w));

	// 无向邻接矩阵主对角线对称
	if (!g->edges[e.v][e.w]) { // edge e not in graph
		g->edges[e.v][e.w] = 1;
		g->edges[e.w][e.v] = 1;
		g->nE++;
	}
}

// 删除边
void removeEdge(Graph g, Edge e)
{
	assert(g != NULL && validV(g, e.v) && validV(g, e.w));

	// 无向邻接矩阵主对角线对称
	if (g->edges[e.v][e.w]) { // edge e in graph
		g->edges[e.v][e.w] = 0;
		g->edges[e.w][e.v] = 0;
		g->nE--;
	}
}

// 边是否存在
bool adjacent(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g, v) && validV(g, w));

	return (g->edges[v][w] != 0);
}

// 打印图
void showGraph(Graph g)
{
	assert(g != NULL);
	int i, j;

	printf("Number of vertices: %d\n", g->nV);
	printf("Number of edges: %d\n", g->nE);
	for (i = 0; i < g->nV; i++) {
		for (j = i + 1; j < g->nV; j++) {
			if (g->edges[i][j]) {
				printf("Edge %d - %d\n", i, j);
			}
		}
	}
}

// 释放图
void freeGraph(Graph g)
{
	assert(g != NULL);

	int i;
	for (i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}
