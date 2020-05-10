#include "Graph.h"

Graph::Graph(int id, int graph_type, int V)
{
	id_ = id;
	graph_type_ = graph_type;
	V_ = V;
	std::cout << "\nCreated ";
	if (graph_type_ == 0) std::cout << "un";
	std::cout << "directed graph with id: " << id_ << ". " << std::endl;
}

Graph::Graph(const Graph* org_graph)
{
	id_ = org_graph->id_ + rand() % 1000 + 100;
	graph_type_ = org_graph->graph_type_;
	V_ = org_graph->V_;
	for (auto i = 0; i < org_graph->V_; i++)
	{
		vertices_.push_back(new Vertex(org_graph->graph_type_, org_graph->vertices_[i]->getId(),
			org_graph->vertices_[i]->getMaxDegreeOut(), org_graph->vertices_[i]->getMaxDegreeIn()));
	}
	for (auto i = 0; i < org_graph->edges_.size(); i++)
	{
		edges_.push_back(new Edge(vertices_[org_graph->edges_[i]->getSrcVertex()->getId()],
			vertices_[org_graph->edges_[i]->getDestVertex()->getId()], org_graph->edges_[i]->getWeight()));
	}
	std::cout << "\nCreated ";
	if (graph_type_ == 0) std::cout << "un";
	std::cout << "directed temporary graph with id: " << id_ << ". " << std::endl;
}

Graph::~Graph()
{
	std::vector<Edge*>().swap(edges_);
	std::vector<Vertex*>().swap(vertices_);
	std::cout << "\nGraph with id " << id_ << " has been removed." << std::endl;
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

void Graph::genEdges() // generates edges until edges make a complete graph
{
	do
	{
		// resets edges and vertices
		std::vector<Edge*>().swap(edges_);
		for (auto i = 0; i < vertices_.size(); i++)
		{
			vertices_[i]->removeAllConn();
		}
		for (int i = 0; i < V_; i++)
		{
			for (int j = 0; j < V_; j++)
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
								edges_.push_back(new Edge(vertices_[i], vertices_[j]));
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
								edges_.push_back(new Edge(vertices_[i], vertices_[j]));
							}
						}
					}
				}
			}
		}
	} while (!checkForCompleteGraph());
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
		auto k = adjListOut.size();
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

bool Graph::checkForCompleteGraph() // returns true for complete graph
{
	std::vector<bool> visited; // creates vector for visited vertexes
	int visitedCounter = 0; // checksum to make sure every vertex has been visited
	for (int i = 0; i < vertices_.size(); i++) // defaults all vector to false
	{
		visited.push_back(false);
	}
	std::stack<Vertex*> stack; // creates stack for pointers to vertexes
	int startVertex = rand() % vertices_.size(); // randomly picks vertex
	stack.push(vertices_[startVertex]); // adds start vertex to the stack to process

	while (!stack.empty()) // exits when the queue is empty
	{
		Vertex* currVertex = stack.top(); // points to the top of the stack
		stack.pop();	// pops the top vertex from the stack

		if (!visited[currVertex->getId()])
		{
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
	if (vertices_.size() == visitedCounter) return true;
	else return false;
}

void Graph::doBfs()
{
	std::vector<bool> visited; // creates vector for visited vertexes
	int visitedCounter = 0; // checksum to make sure every vertex has been visited
	for (int i = 0; i < vertices_.size(); i++) // defaults visited to false
	{
		visited.push_back(false);
	}
	std::list<Vertex*> queue; // creates queue for pointers to vertexes

	while (vertices_.size() != visitedCounter)
	{
		int startVertex = 0;
		do
		{
			startVertex = rand() % vertices_.size(); // randomly picks vertex
		} while (visited[startVertex]); // exits when unvisited vertex has been chosen

		visited[startVertex] = true; // notes that start vertex has been visited
		visitedCounter++;

		queue.push_back(vertices_[startVertex]); // adds start vertex to the queue to process

		std::cout << "\nGraph " << id_ << " BFS: ";
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

	while (vertices_.size() != visitedCounter)
	{
		int startVertex = 0;
		do
		{
			startVertex = rand() % vertices_.size(); // randomly picks vertex
		} while (visited[startVertex]); // exits when unvisited vertex has been chosen

		stack.push(vertices_[startVertex]); // adds start vertex to the stack to process

		std::cout << "\nGraph " << id_ << " DFS: ";
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

void Graph::doKruskals()
{
	int mst_edges_count = V_ - 1; // Minimum Spanning Tree edges count
	Graph temp_graph = this; //  copy graph
	temp_graph.doSortEdges(); // sort edges
	std::vector<Edge*> temp_edges = temp_graph.edges_; // copy edges to temporary vector
	temp_graph.removeAllEdges(); // remove all the edges 
	for (auto i = 0; i < temp_edges.size(); i++)
	{
		temp_graph.addEdge(temp_edges[i]);
		if (temp_graph.checkForCycle()) temp_graph.removeRecentlyAddedEdge(); // if cyle formed then pop back recently added edge and pick
		// another edge
		if (temp_graph.getEdgeCount() == mst_edges_count) break; // statement to break the loop when all 
		// required edges has been added
	}
	std::cout << "Kruskal's algorithm results: " << std::endl;
	temp_graph.dispAdjMatrix();
	temp_graph.dispAdjList();

	int script_type = 0;
	std::cout << "\nSelect search script [ BFS - 1 | DFS - 0 ]: ";
	std::cin >> script_type;
	if (script_type == 1) temp_graph.doBfs();
	else temp_graph.doDfs();
}

void Graph::doPrims()
{
	doSortEdges();
}

void Graph::doSortEdges()
{
	sort(edges_.begin(), edges_.end(), weightComp);
}

bool Graph::weightComp(Edge* edge_a, Edge* edge_b)
{
	if (edge_a->getWeight() < edge_b->getWeight()) return true;
	else return false;
}

void Graph::addEdge(Edge* edge)
{
	edges_.push_back(edge);
	edge->getSrcVertex()->addConnOut(edge->getDestVertex());
	if (graph_type_ == 1) edge->getDestVertex()->addConnIn(edge->getSrcVertex());
	else edge->getDestVertex()->addConnOut(edge->getSrcVertex());
}

void Graph::removeRecentlyAddedEdge()
{
	edges_[edges_.size() - 1]->getSrcVertex()->removeConnOut();
	if (graph_type_ == 1) edges_[edges_.size() - 1]->getDestVertex()->removeConnIn();
	else edges_[edges_.size() - 1]->getDestVertex()->removeConnOut();
	edges_.pop_back();
}

bool Graph::checkForCycle() // return true if cycle is formed, otherwise return false
{
	if (graph_type_ == 1)
	{
		std::vector<bool> visited; // creates vector for visited vertexes
		for (int i = 0; i < vertices_.size(); i++) // defaults visited to false
		{
			visited.push_back(false);
		}
		std::list<Vertex*> queue; // creates queue for pointers to vertexes

		int startVertex = edges_[0]->getSrcVertex()->getId(); // get the id of the first vertex
		visited[startVertex] = true; // notes that start vertex has been visited

		queue.push_back(vertices_[startVertex]); // adds start vertex to the queue to process

		while (!queue.empty()) // exits when the queue is empty
		{
			Vertex* currVertex = queue.front(); // points to the front of the queue
			queue.pop_front(); // pops the first vertex from the queue
			for (int i = 0; i < currVertex->getAdjListOut().size(); i++) // iterates over adjacency list of that vertex
			{
				Vertex* adjVertex = currVertex->getAdjListOut()[i];
				if (!visited[adjVertex->getId()]) // checks whether this vertex has been visited before
				{
					visited[adjVertex->getId()] = true; // if not, marks as visited
					queue.push_back(adjVertex); // appends to queue
				}
				else return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

void Graph::removeAllEdges()
{
	std::vector<Edge*>().swap(edges_);
}

std::vector<Edge*> Graph::getEdges()
{
	return edges_;
}

int Graph::getEdgeCount()
{
	return edges_.size();
}


bool Graph::genConn()
{
	int conn = rand() % 4;
	if (conn == 0) return false;
	else return true;
}
