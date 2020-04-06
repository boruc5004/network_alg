#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <list>
#include <stack>
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
	vector<Vertex*> getAdjListIn()
	{
		return adjListIn;
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

void dispAdjMatrix(vector<Vertex> &const vertexes)
{
	cout << "\nAdjacency Matrix:" << endl;
	for (int i = 0; i < vertexes.size(); i++)
	{
		vector<Vertex*> adjListOut = vertexes[i].getAdjListOut(); // vector of pointers to adjacent vertexes
		int k = adjListOut.size();
		for (int j = 0; j < vertexes.size(); j++)
		{
			if (i == j) cout << "0 ";
			else
			{
				if (k > 0)
				{
					if (adjListOut[(adjListOut.size()-1)-(k-1)]->getId() == j) // checks wheather there are any adjacent vertexes left on a list,
																				// if not it fills the table with zeros
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

void dispAdjList(vector<Vertex> &const vertexes)
{
	cout << "\nAdjacency List:" << endl;
	for (int i = 0; i < vertexes.size(); i++)
	{
		cout << vertexes[i].getId() << ":";
		vertexes[i].dispAdjListOut();
		cout << endl;
	}
}

void doBfs(vector<Vertex> &const vertexes)
{
	vector<bool> visited; // creates vector for visited vertexes
	int visitedCounter = 0; // checksum to make sure every vertex has been visited
	for (int i = 0; i < vertexes.size(); i++) // defaults all vector to false
	{
		visited.push_back(false);
	}
	list<Vertex*> queue; // creates queue for pointers to vertexes

	while (vertexes.size()-1 != visitedCounter)
	{
		int startVertex = 0;
		do
		{
			startVertex = rand() % vertexes.size(); // randomly picks vertex
		} while (visited[startVertex]); // exits when unvisited vertex has been chosen

		visited[startVertex] = true; // notes that start vertex has been visited

		queue.push_back(&vertexes[startVertex]); // adds start vertex to the queue to process

		cout << "\nBFS: ";
		while (!queue.empty()) // exits when the queue is empty
		{
			Vertex* currVertex = queue.front(); // points to the front of the queue
			cout << " -> " << currVertex->getId(); // states that this vertex has been visited
			queue.pop_front(); // pops the first vertex from the queue
			for (int i = 0; i < currVertex->getAdjListOut().size(); i++) // iterates over adjacency list of that vertex
			{
				Vertex* adjVertex = currVertex->getAdjListOut()[i];
				if (!visited[adjVertex->getId()]) // checks whether this vertex has been visited before
				{
					visited[adjVertex->getId()] = true; // if not, marks as visited
					visitedCounter++;
					queue.push_back(adjVertex); // appends to queue
				}
			}

		}
	}
}

void doDfs(vector<Vertex>& const vertexes)
{
	vector<bool> visited; // creates vector for visited vertexes
	int visitedCounter = 0; // checksum to make sure every vertex has been visited
	for (int i = 0; i < vertexes.size(); i++) // defaults all vector to false
	{
		visited.push_back(false);
	}
	stack<Vertex*> stack; // creates stack for pointers to vertexes

	while (vertexes.size()-1 != visitedCounter)
	{
		int startVertex = 0;
		do
		{
			startVertex = rand() % vertexes.size(); // randomly picks vertex
		} while (visited[startVertex]); // exits when unvisited vertex has been chosen

		stack.push(&vertexes[startVertex]); // adds start vertex to the stack to process

		cout << "\nDFS: ";
		while (!stack.empty()) // exits when the queue is empty
		{
			Vertex* currVertex = stack.top(); // points to the top of the stack
			stack.pop();	// pops the top vertex from the stack

			if (!visited[currVertex->getId()])
			{
				cout << " -> " << currVertex->getId(); // states that this vertex has been visited
				visited[currVertex->getId()] = true;
				visitedCounter++;
			}
			
			for (int i = currVertex->getAdjListOut().size() - 1 ; i >= 0; i--) // iterates over adjacency list of that vertex
			{
				Vertex* adjVertex = currVertex->getAdjListOut()[i];
				if (!visited[adjVertex->getId()]) // checks whether this vertex has been visited before
				{
					stack.push(adjVertex); // appends to queue
				}
			}
		}
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
	for (int i = 0; i < (max_node_degree_out + rand()%5); i++) // generates vertexes. Vertex count = maximal degree out + random(0-4)
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
			else {
				if (graph_type == 0 && !(j < i)) // Undirected Graph
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
				else if (graph_type == 1)// Directed Graph
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
	
	dispAdjMatrix(vertexes);
	dispAdjList(vertexes);

	int script_type = 0;
	cout << "\nSelect search script [ BFS - 1 | DFS - 0 ]: ";
	cin >> script_type;

	if (script_type == 1) doBfs(vertexes); // BFS
	else doDfs(vertexes); // DFS

	vector<Vertex>().swap(vertexes); // Release memory after vector

	return 0;

}