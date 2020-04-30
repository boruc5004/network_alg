#include "Vertex.h"

Vertex::Vertex(int graph_type, int v_id, int max_node_degree_out, int max_node_degree_in)
{
	id = v_id;
	max_degree_out = rand() % max_node_degree_out + 1;
	if (graph_type == 1) max_degree_in = rand() % max_node_degree_in + 1;
	else max_degree_in = 0;
}

Vertex::~Vertex()
{
	std::vector<Vertex*>().swap(adjListOut);
	std::vector<Vertex*>().swap(adjListIn);
}

int Vertex::getMaxDegreeOut()
{
	return max_degree_out;
}

int Vertex::getMaxDegreeIn()
{
	return max_degree_in;
}

int Vertex::getAvailConnOut()
{
	return max_degree_out - adjListOut.size();
}

int Vertex::getAvailConnIn()
{
	return max_degree_in - adjListIn.size();
}

int Vertex::getId()
{
	return id;
}

std::vector<Vertex*> Vertex::getAdjListOut()
{
	return adjListOut;
}

std::vector<Vertex*> Vertex::getAdjListIn()
{
	return adjListIn;
}

void Vertex::addConnIn(Vertex* vertexPtr)
{
	adjListIn.push_back(vertexPtr);
}

void Vertex::addConnOut(Vertex* vertexPtr)
{
	adjListOut.push_back(vertexPtr);
}

void Vertex::dispAdjListOut()
{
	for (int i = 0; i < adjListOut.size(); i++)
	{
		std::cout << " -> " << adjListOut[i]->getId();
	}
}
