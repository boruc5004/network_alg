#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class Vertex {

	int id, max_degree_out, max_degree_in;
	vector<Vertex*> adjListIn, adjListOut;

public:

	Vertex(int graph_type, int v_id, int max_node_degree_out, int max_node_degree_in) {

		id = v_id;
		max_degree_out = rand() % max_node_degree_out + 1;
		if (graph_type == 1) max_degree_in = rand() % max_node_degree_in + 1;
		else max_degree_in = 0;

	}
	~Vertex() { /** ????  ???? **/ }

	int getMaxDegreeOut()
	{
		return max_degree_out;
	}
	int getMaxDegreeIn()
	{
		return max_degree_in;
	}
	int getAvailConnOut()
	{
		return max_degree_out - adjListOut.size();
	}
	int getAvailConnIn()
	{
		return max_degree_in - adjListIn.size();
	}
	int getId()
	{
		return id;
	}
	void addConnIn(Vertex* vertexPtr)
	{
		adjListIn.push_back(vertexPtr);
	}
	void addConnOut(Vertex* vertexPtr)
	{
		adjListOut.push_back(vertexPtr);
	}
	void dispAdjListOut()
	{
		for (int i = 0; i < adjListOut.size(); i++)
		{
			cout << " -> " << adjListOut[i]->getId();
		}
	}
	
};

bool genConn()
{
	int conn = rand() % 2;
	if (conn == 0) return false;
	else return true;
}

void dispAdjMatrix(int** AdjTab, int N)
{
	cout << "\nAdjacency Matrix:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << AdjTab[i][j] << " ";
		}
		cout << endl;
	}
}

void dispAdjList(vector<Vertex> &const vertexes, int N)
{
	cout << "\nAdjacency List:" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << vertexes[i].getId() << ":";
		vertexes[i].dispAdjListOut();
		cout << endl;
	}
}

int main()
{
	srand(time(NULL));

	int max_node_degree_out = 0, max_node_degree_in = 0; //Max degree of the node
	int graph_type = 0; //1 - directed; 0 - undirected

	do {
		cout << "Choose type of the Graph [ 1 - Directed | 0 - Undirected ]: "; cin >> graph_type;
	} while (graph_type > 1 || graph_type < 0);

	if (graph_type == 1)
	{
		do {
			cout << "Type in maximal degree of a node [outgoing]: "; cin >> max_node_degree_out;
		} while (max_node_degree_out <= 0);
		do {
			cout << "Type in maximal degree of a node [incoming]: "; cin >> max_node_degree_in;
		} while (max_node_degree_in <= 0);
	}
	else {
		do {
			cout << "Type in maximal degree of a node: "; cin >> max_node_degree_out;
		} while (max_node_degree_out <= 0);
	}

	vector<Vertex> vertexes;
	for (int i = 0; i < (max_node_degree_out + rand()%5); i++)
	{
		vertexes.push_back( Vertex ( graph_type, i, max_node_degree_out, max_node_degree_in ) );
	}
	cout << "Created " << vertexes.size() << " vertexes." << endl;

	// Dynamically allocated table for Adjacency Matrix
	int** AdjTab = new int* [vertexes.size()];
	for (int i = 0; i < vertexes.size(); i++)
	{
		AdjTab[i] = new int[vertexes.size()];
	}

	// Generating Edges
	if (graph_type == 0) // Undirected Graph
	{
		for (int i = 0; i < vertexes.size(); i++)
		{
			for (int j = 0; j < vertexes.size(); j++)
			{
				if (i == j) {
					AdjTab[i][j] = 0;
				}
				else if (j < i) {
					AdjTab[i][j] = AdjTab[j][i];
				}
				else {
					if (vertexes[i].getAvailConnOut() > 0 && vertexes[j].getAvailConnOut() > 0)
					{
						if (genConn()) // 50% chance to create an edge between vertexes
						{
							vertexes[i].addConnOut(&vertexes[j]);
							vertexes[j].addConnOut(&vertexes[i]);
							AdjTab[i][j] = 1;
						}
						else AdjTab[i][j] = 0;
					}
					else AdjTab[i][j] = 0;
				}
			}
		}
	}
	else // Directed Graph
	{
		for (int i = 0; i < vertexes.size(); i++)
		{
			for (int j = 0; j < vertexes.size(); j++)
			{
				if (i == j) {
					AdjTab[i][j] = 0;
				}
				else {
					if (vertexes[i].getAvailConnOut() > 0 && vertexes[j].getAvailConnIn() > 0)
					{
						if (genConn()) // 50% chance to create an edge between vertexes
						{
							vertexes[i].addConnOut(&vertexes[j]);
							vertexes[j].addConnIn(&vertexes[i]);
							AdjTab[i][j] = 1;
						}
						else AdjTab[i][j] = 0;
					}
					else AdjTab[i][j] = 0;
				}
			}
		}
	}
	
	dispAdjMatrix(AdjTab,vertexes.size());
	dispAdjList(vertexes,vertexes.size());

	delete[] AdjTab;

	return 0;

}