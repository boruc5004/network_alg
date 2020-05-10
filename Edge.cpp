#include "Edge.h"

Edge::Edge(Vertex* src_vertex, Vertex* dest_vertex)
{
	src_vertex_ = src_vertex;
	dest_vertex_ = dest_vertex;
	weight_ = rand() % 20 + 1;
}

Edge::Edge(Vertex* src_vertex, Vertex* dest_vertex, int weight)
{
	src_vertex_ = src_vertex;
	dest_vertex_ = dest_vertex;
	weight_ = weight;
}

int Edge::getWeight()
{
	return weight_;
}

Vertex* Edge::getSrcVertex()
{
	return src_vertex_;
}

Vertex* Edge::getDestVertex()
{
	return dest_vertex_;
}
