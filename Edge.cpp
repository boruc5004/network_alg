#include "Edge.h"

Edge::Edge(Vertex* src_vertex, Vertex* dest_vertex, int weight)
{
	src_vertex_ = src_vertex;
	dest_vertex_ = dest_vertex;
	weight_ = weight;
}
