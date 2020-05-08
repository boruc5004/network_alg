#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include "Graph.h"

using namespace std;

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

	int number_of_verticies = max_node_degree_out + rand() % 5; //  Vertex count = maximal degree out + random(0-4)
	Graph* graph = new Graph(0, graph_type, number_of_verticies, number_of_verticies); 
	graph->genVertices(max_node_degree_out, max_node_degree_in);
	graph->genEdges();

	graph->dispAdjMatrix();
	graph->dispAdjList();

	int script_type = 0;
	cout << "\nSelect search script [ BFS - 1 | DFS - 0 ]: ";
	cin >> script_type;

	if (script_type == 1) graph->doBfs();
	else graph->doDfs();

	cout << "\n\nSelect MST algorithm [ Kruskal's - 1 | Prim's - 0 ]: ";
	cin >> script_type;

	if (script_type == 1) graph->doKruskals(); 
	else graph->doPrims();

	return 0;

}