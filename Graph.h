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
	bool checkForCycleUtil(Vertex* v, bool visited[], int parent);
	int minKey(std::vector<int> key, std::vector<bool> mstSet);
	Edge* matchEdge(std::vector<Edge*> edges, Vertex* src_vertex, Vertex* dest_vertex);

public:

	Graph(int id, int graph_type, int V);
	Graph(const Graph* org_graph);
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
	std::vector<Edge*> getEdges();
	int getEdgeCount();
	static bool weightComp(Edge* edge_a, Edge* edge_b);
	void addEdge(Edge* edge);
	void removeRecentlyAddedEdge();
	bool checkForCycle();
	bool checkIsComplete();
	void removeAllEdges();
	void removeAllVertices();

};
#endif
