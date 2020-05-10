#include "Vertex.h"

Vertex::Vertex(int graph_type, int v_id, int max_node_degree_out, int max_node_degree_in)
{
	id_ = v_id;
	max_degree_out_ = rand() % max_node_degree_out + 1;
	if (graph_type == 1) max_degree_in_ = rand() % max_node_degree_in + 1;
	else max_degree_in_ = 0;
}

Vertex::~Vertex()
{
	std::vector<Vertex*>().swap(adjListOut_);
	std::vector<Vertex*>().swap(adjListIn_);
}

int Vertex::getMaxDegreeOut()
{
	return max_degree_out_;
}

int Vertex::getMaxDegreeIn()
{
	return max_degree_in_;
}

int Vertex::getAvailConnOut()
{
	return max_degree_out_ - adjListOut_.size();
}

int Vertex::getAvailConnIn()
{
	return max_degree_in_ - adjListIn_.size();
}

int Vertex::getId()
{
	return id_;
}

std::vector<Vertex*> Vertex::getAdjListOut()
{
	return adjListOut_;
}

std::vector<Vertex*> Vertex::getAdjListIn()
{
	return adjListIn_;
}

void Vertex::addConnIn(Vertex* vertexPtr)
{
	adjListIn_.push_back(vertexPtr);
}

void Vertex::addConnOut(Vertex* vertexPtr)
{
	adjListOut_.push_back(vertexPtr);
}

void Vertex::removeConnIn()
{
	adjListIn_.pop_back();
}

void Vertex::removeConnOut()
{
	adjListOut_.pop_back();
}

void Vertex::removeAllConn()
{
	std::vector<Vertex*>().swap(adjListOut_);
	std::vector<Vertex*>().swap(adjListIn_);
}

void Vertex::dispAdjListOut()
{
	for (int i = 0; i < adjListOut_.size(); i++)
	{
		std::cout << " -> " << adjListOut_[i]->getId();
	}
}
