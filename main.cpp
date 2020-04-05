#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int max_node_degree_out = 0, max_node_degree_in = 0; //Max degree of the node
int graph_type = 0; //1 - directed; 0 - undirected

class Vertex {

	int max_degree_out, max_degree_in;
	int avail_out_conn, avail_in_conn;

public:

	Vertex() {
		max_degree_out = rand() % max_node_degree_out + 1;
		if (graph_type == 1)
		{
			max_degree_in = rand() % max_node_degree_in + 1;
		}
		else {
			max_degree_in = 0;
		}
		avail_out_conn = max_degree_out;
		avail_in_conn = max_degree_in;
	}
	~Vertex() {}

	int getMaxDegreeOut()
	{
		return max_degree_out;
	}
	int getMaxDegreeIn()
	{
		return max_degree_in;
	}
	int getAvailOutConn()
	{
		return avail_out_conn;
	}
	int getAvailInConn()
	{
		return avail_in_conn;
	}
	void addInConn()
	{
		avail_in_conn -= 1;
	}
	void addOutConn()
	{
		avail_out_conn -= 1;
	}
};

bool genConn()
{
	int conn = rand() % 2;
	if (conn == 0) return false;
	else return true;
}

int main()
{
	srand(time(NULL));

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

	const unsigned int vertex_num = 10; // Change to adjust the number of total Vertexes

	Vertex vertex[vertex_num];

	int AdjTab[vertex_num][vertex_num] = { 0 };

	if (graph_type == 0) // Undirected Graph
	{
		for (int i = 0; i < vertex_num; i++)
		{
			for (int j = 0; j < vertex_num; j++)
			{
				if (i == j) {
					AdjTab[i][j] = 0;
				}
				else if (j < i) {
					AdjTab[i][j] = AdjTab[j][i];
				}
				else {
					if (vertex[i].getAvailOutConn() > 0 && vertex[j].getAvailOutConn() > 0)
					{
						if (genConn())
						{
							vertex[i].addOutConn();
							vertex[j].addOutConn();
							AdjTab[i][j] = 1;
						}
					}
				}
			}
		}
	}
	else // Directed Graph
	{
		for (int i = 0; i < vertex_num; i++)
		{
			for (int j = 0; j < vertex_num; j++)
			{
				if (i == j) {
					AdjTab[i][j] = 0;
				}
				else {
					if (vertex[i].getAvailOutConn() > 0 && vertex[j].getAvailInConn() > 0)
					{
						if (genConn())
						{
							vertex[i].addOutConn();
							vertex[j].addInConn();
							AdjTab[i][j] = 1;
						}
					}
				}
			}
		}
	}
	cout << "\nNodes with corresponding connections:" << endl;
	for (int i = 0; i < vertex_num; i++)
	{
		cout << i + 1;
		for (int j = 0; j < vertex_num; j++)
		{
			if (AdjTab[i][j] == 1) {
				cout << " -> " << j + 1;
			}
		}
		cout << " ;" << endl;
	}
	cout << "\nAdjacency Matrix:" << endl;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
		{
			cout << AdjTab[i][j] << " ";
		}
		cout << endl;
	}

}