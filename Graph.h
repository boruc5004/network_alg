#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>
#include "Edge.h"
#include "Vertex.h"
#include <list>
#include <stack>

class Graph
{
	std::vector<Edge*> edges_;
	std::vector<Edge*> edges_sorted_; // where sorted edges will be
	std::vector<Vertex*> vertices_;
	int graph_type_; // type of a graph, 1 - directed | 0 - undirected
	int V_; // number of vertices
	int E_; // number of edges
	int id_; // id of graph
	bool genConn();

public:

	Graph(int id, int graph_type, int V, int E);
	~Graph();

	void genVertices(int max_degree_out, int max_degree_in);
	void genEdges();
	void dispAdjList();
	void dispAdjMatrix();
	void doBfs();
	void doDfs();
	void doKruskals();
	void doPrims();
	void doSortEdges();
	int weightComp(const void* vert_a, const void* vert_b);

};
#endif
