#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>
#include "Edge.h"
#include "Vertex.h"
#include <list>
#include <stack>
#include <algorithm>

class Graph
{
	std::vector<Edge*> edges_;
	std::vector<Vertex*> vertices_;
	int graph_type_; // type of a graph, 1 - directed | 0 - undirected
	int V_; // number of vertices
	int id_; // id of graph
	bool genConn();

public:

	Graph(int id, int graph_type, int V);
	Graph(const Graph* org_graph);
	~Graph();

	void genVertices(int max_degree_out, int max_degree_in);
	void genEdges();
	void dispAdjList();
	void dispAdjMatrix();
	bool checkForCompleteGraph();
	void doBfs();
	void doDfs();
	void doKruskals();
	void doPrims();
	void doSortEdges();
	std::vector<Edge*> getEdges();
	int getEdgeCount();
	static bool weightComp(Edge* edge_a, Edge* edge_b);
	void addEdge(Edge* edge);
	void removeRecentlyAddedEdge();
	bool checkForCycle();
	void removeAllEdges();

};
#endif
