#include "Graph.h"

Graph::Graph(int id, int graph_type, int V, int E)
{
	id_ = id;
	graph_type_ = graph_type;
	V_ = V;
	E_ = E;
	std::cout << "Created ";
	if (graph_type_ == 0) std::cout << "un";
	std::cout << "directed graph with id: " << id_ << ". " << std::endl;
}

Graph::~Graph()
{
	std::vector<Edge*>().swap(edges_);
	std::vector<Vertex*>().swap(vertices_);
}

void Graph::genVertices(int max_degree_out, int max_degree_in)
{
	for (int i = 0; i < V_; i++)
	{
		Vertex* temp_vertex = new Vertex(graph_type_, i, max_degree_out, max_degree_in);
		vertices_.push_back(temp_vertex);
	}
	std::cout << "Graph " << id_ << " has generated " << vertices_.size() << " vertices." << std::endl;
}

void Graph::genEdges()
{
	for (int i = 0; i < E_; i++)
	{
		for (int j = 0; j < E_; j++)
		{
			if (i == j);
			else {
				if (graph_type_ == 0 && !(j < i)) // Undirected Graph
				{
					if (vertices_[i]->getAvailConnOut() > 0 && vertices_[j]->getAvailConnOut() > 0)
					{
						if (genConn()) // 25% chance to create an edge between vertexes
						{
							vertices_[i]->addConnOut(vertices_[j]);
							vertices_[j]->addConnOut(vertices_[i]);
							Edge* edge = new Edge(vertices_[i], vertices_[j], rand()%20 + 1);
							edges_.push_back(edge);
						}
					}
				}
				else if (graph_type_ == 1)// Directed Graph
				{
					if (vertices_[i]->getAvailConnOut() > 0 && vertices_[j]->getAvailConnIn() > 0)
					{
						if (genConn()) // 25% chance to create an edge between vertexes
						{
							vertices_[i]->addConnOut(vertices_[j]);
							vertices_[j]->addConnIn(vertices_[i]);
							Edge* edge = new Edge(vertices_[i], vertices_[j], rand() % 20 + 1);
							edges_.push_back(edge);
						}
					}
				}
			}
		}
	}
	std::cout << "Graph " << id_ << " has generated " << edges_.size() << " edges." << std::endl;
}

void Graph::dispAdjList()
{
	std::cout << "\nAdjacency List of Graph " << id_ << ":" << std::endl;
	for (int i = 0; i < vertices_.size(); i++)
	{
		std::cout << vertices_[i]->getId() << ":";
		vertices_[i]->dispAdjListOut();
		std::cout << std::endl;
	}
}

void Graph::dispAdjMatrix()
{
	std::cout << "\nAdjacency Matrix of Graph " << id_ << ":" << std::endl;
	for (int i = 0; i < vertices_.size(); i++)
	{
		std::vector<Vertex*> adjListOut = vertices_[i]->getAdjListOut(); // vector of pointers to adjacent vertexes
		int k = adjListOut.size();
		for (int j = 0; j < vertices_.size(); j++)
		{
			if (i == j) std::cout << "0 ";
			else
			{
				if (k > 0)
				{
					if (adjListOut[(adjListOut.size() - 1) - (k - 1)]->getId() == j) // checks wheather there are any adjacent vertexes left on a list,
																				// if not it fills the table with zeros
					{
						std::cout << "1 ";
						k--;
					}
					else std::cout << "0 ";
				}
				else std::cout << "0 ";
			}
		}
		std::cout << std::endl;
	}
}

void Graph::doBfs()
{
	std::vector<bool> visited; // creates vector for visited vertexes
	int visitedCounter = 0; // checksum to make sure every vertex has been visited
	for (int i = 0; i < vertices_.size(); i++) // defaults all vector to false
	{
		visited.push_back(false);
	}
	std::list<Vertex*> queue; // creates queue for pointers to vertexes

	while (vertices_.size() - 1 != visitedCounter)
	{
		int startVertex = 0;
		do
		{
			startVertex = rand() % vertices_.size(); // randomly picks vertex
		} while (visited[startVertex]); // exits when unvisited vertex has been chosen

		visited[startVertex] = true; // notes that start vertex has been visited

		queue.push_back(vertices_[startVertex]); // adds start vertex to the queue to process

		std::cout << "\nBFS: ";
		while (!queue.empty()) // exits when the queue is empty
		{
			Vertex* currVertex = queue.front(); // points to the front of the queue
			std::cout << " -> " << currVertex->getId(); // states that this vertex has been visited
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

void Graph::doDfs()
{
	std::vector<bool> visited; // creates vector for visited vertexes
	int visitedCounter = 0; // checksum to make sure every vertex has been visited
	for (int i = 0; i < vertices_.size(); i++) // defaults all vector to false
	{
		visited.push_back(false);
	}
	std::stack<Vertex*> stack; // creates stack for pointers to vertexes

	while (vertices_.size() - 1 != visitedCounter)
	{
		int startVertex = 0;
		do
		{
			startVertex = rand() % vertices_.size(); // randomly picks vertex
		} while (visited[startVertex]); // exits when unvisited vertex has been chosen

		stack.push(vertices_[startVertex]); // adds start vertex to the stack to process

		std::cout << "\nDFS: ";
		while (!stack.empty()) // exits when the queue is empty
		{
			Vertex* currVertex = stack.top(); // points to the top of the stack
			stack.pop();	// pops the top vertex from the stack

			if (!visited[currVertex->getId()])
			{
				std::cout << " -> " << currVertex->getId(); // states that this vertex has been visited
				visited[currVertex->getId()] = true;
				visitedCounter++;
			}

			for (int i = currVertex->getAdjListOut().size() - 1; i >= 0; i--) // iterates over adjacency list of that vertex
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

bool Graph::genConn()
{
	int conn = rand() % 4;
	if (conn == 0) return false;
	else return true;
}
