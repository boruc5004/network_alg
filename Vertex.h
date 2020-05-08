#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>
#include <time.h>
#include <iostream>

class Vertex {

	int max_degree_out_, max_degree_in_;
	int id_;
	std::vector<Vertex*> adjListIn_, adjListOut_;

public:

	Vertex(int graph_type, int v_id, int max_node_degree_out, int max_node_degree_in);
	~Vertex();
	int getMaxDegreeOut();
	int getMaxDegreeIn();
	int getAvailConnOut();
	int getAvailConnIn();
	int getId();
	std::vector<Vertex*> getAdjListOut();
	std::vector<Vertex*> getAdjListIn();
	void addConnIn(Vertex* vertexPtr);
	void addConnOut(Vertex* vertexPtr);
	void dispAdjListOut();
};
#endif

