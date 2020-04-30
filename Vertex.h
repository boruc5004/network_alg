#include <vector>
#include <time.h>
#include <iostream>

class Vertex {

	int id, max_degree_out, max_degree_in;
	std::vector<Vertex*> adjListIn, adjListOut;

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

