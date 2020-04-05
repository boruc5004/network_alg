#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

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
	~Vertex() 
	{
		vector<Vertex*>().swap(adjListOut);
		vector<Vertex*>().swap(adjListIn);
	}

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
	vector<Vertex*> getAdjListOut()
	{
		return adjListOut;
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
	int conn = rand() % 4;
	if (conn == 0) return false;
	else return true;
}

void dispAdjMatrix(vector<Vertex> &const vertexes, int N)
{
	cout << "\nAdjacency Matrix:" << endl;
	for (int i = 0; i < N; i++)
	{
		vector<Vertex*> adjListOut = vertexes[i].getAdjListOut();
		int k = adjListOut.size();
		for (int j = 0; j < N; j++)
		{
			if (i == j) cout << "0 ";
			else
			{
				if (k > 0)
				{
					if (adjListOut[(adjListOut.size()-1)-(k-1)]->getId() == j)
					{
						cout << "1 ";
						k--;
					}
					else cout << "0 ";
				}
				else cout << "0 ";
			}
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

	// Generating Edges
	for (int i = 0; i < vertexes.size(); i++)
	{
		for (int j = 0; j < vertexes.size(); j++)
		{
			if (i == j);
			else if (j < i);
			else {
				if (graph_type == 0) // Undirected Graph
				{
					if (vertexes[i].getAvailConnOut() > 0 && vertexes[j].getAvailConnOut() > 0)
					{
						if (genConn()) // 25% chance to create an edge between vertexes
						{
							vertexes[i].addConnOut(&vertexes[j]);
							vertexes[j].addConnOut(&vertexes[i]);
						}
					}
				}
				else // Directed Graph
				{
					if (vertexes[i].getAvailConnOut() > 0 && vertexes[j].getAvailConnIn() > 0)
					{
						if (genConn()) // 25% chance to create an edge between vertexes
						{
							vertexes[i].addConnOut(&vertexes[j]);
							vertexes[j].addConnIn(&vertexes[i]);
						}
					}
				}
			}
		}
	}
	
	dispAdjMatrix(vertexes,vertexes.size());
	dispAdjList(vertexes,vertexes.size());

	vector<Vertex>().swap(vertexes); // Release memory after vector

	return 0;

}