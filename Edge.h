#ifndef EDGE_H_
#define EDGE_H_

#include <vector>
#include "Vertex.h"

class Edge
{
	Vertex* src_vertex_;
	Vertex* dest_vertex_;
	int weight_;

public:

	Edge(Vertex* src_vertex, Vertex* dest_vertex, int weight);
	~Edge();
	int getWeight();
	Vertex* getSrcVertex();
	Vertex* getDestVertex();

};
#endif
