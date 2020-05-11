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
		while (!stack.empty()) // exits when the stack is empty
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
					stack.push(adjVertex); // appends to stack
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
	temp_graph.removeAllEdges(); // remove all the edges from the temporary graph
	for (auto i = 0; i < temp_edges.size(); i++)
	{
		temp_graph.addEdge(temp_edges[i]);
		if (temp_graph.checkForCycle()) temp_graph.removeRecentlyAddedEdge(); // if cyle formed then pop 
		//back recently added edge and pick another edge
		if (temp_graph.getEdgeCount() == mst_edges_count) break; // statement to break the loop when all 
		// required edges has been added
	}
	std::cout << "\nKruskal's algorithm results: " << std::endl;
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
	int* key = new int[V_]; // Key values used to pick minimum weight edge in cut  
	bool* mstSet = new bool[V_]; // To represent set of vertices not yet included in MST  
	Graph tmp_graph = this; //  Copy graph
	std::vector<Edge*> tmp_edges = tmp_graph.edges_; // Copy edges to temporary vector
	tmp_graph.removeAllEdges(); // Remove all the edges from the temporary graph

	// Initialize all keys as INFINITE  
	for (int i = 0; i < V_; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0; // Vertex with id 0 will be picked first
	for (auto i = 0; i < V_-1; i++)
	{
		int u = minKey(key, mstSet); // Pick the minimum key vertex from the  
        // set of vertices not yet included in MST  

		mstSet[u] = true; // Add the picked vertex to the MST Set 
		for (int v = 0; v < this->vertices_[u]->getAdjListOut().size(); v++)
		{
			Edge* tmp_edge = matchEdge(tmp_edges, tmp_graph.vertices_[u], tmp_graph.vertices_[this->vertices_[u]->getAdjListOut()[v]->getId()]); // find connecting edge between vertices
			if (mstSet[v] == false &&  tmp_edge->getWeight() < key[v]) // update key only if it's smaller then current;
				//consider only those vertices which are not yet included in MST
			{
				key[v] = tmp_edge->getWeight(); // update the key value
				tmp_graph.addEdge(tmp_edge); // add this edge to the graph
			}
		}
	}
	std::cout << "\Prim's algorithm results: " << std::endl;
	tmp_graph.dispAdjMatrix();
	tmp_graph.dispAdjList();

	int script_type = 0;
	std::cout << "\nSelect search script [ BFS - 1 | DFS - 0 ]: ";
	std::cin >> script_type;
	if (script_type == 1) tmp_graph.doBfs();
	else tmp_graph.doDfs();
}

int Graph::minKey(int key[], bool mstSet[])
{
	int min = INT_MAX, min_index{};
	for (int v = 0; v < V_; v++)
	{
		if (mstSet[v] == false && key[v] < min)
		{
			min = key[v], min_index = v;
		}
	}
	return min_index;
}

Edge* Graph::matchEdge(std::vector<Edge*> edges, Vertex* src_vertex, Vertex* dest_vertex)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i]->getSrcVertex() == src_vertex && edges[i]->getDestVertex() == dest_vertex)
		{
			return edges[i];
		}
	}
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i]->getSrcVertex() == dest_vertex && edges[i]->getDestVertex() == src_vertex)
		{
			return edges[i];
		}
	}
	return nullptr;
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
	// Mark all the vertices as not visited and not part of recursion stack
	bool* visited = new bool[V_];
	for (int i = 0; i < V_; i++)
		visited[i] = false;

	// Call the recursive helper function to detect cycle in different DFS trees 
	for (int i = 0; i < V_; i++)
		if (!visited[i]) // Don't recur for i if it is already visited 
			if (checkForCycleUtil(vertices_[i], visited, -1))
				return true;
	return false;
}

bool Graph::checkForCycleUtil(Vertex* v, bool visited[], int parent)
{
	// Mark the current node as visited 
	visited[v->getId()] = true;

	// Recur for all the vertices adjacent to this vertex 
	for (auto i = 0; i < v->getAdjListOut().size(); ++i)
	{
		// If an adjacent is not visited, then recur for that adjacent 
		if (!visited[v->getAdjListOut()[i]->getId()])
		{
			if (checkForCycleUtil(v->getAdjListOut()[i], visited, v->getId()))
				return true;
		}

		// If an adjacent is visited and not parent of current vertex, 
		// then there is a cycle. 
		else if (v->getAdjListOut()[i]->getId() != parent)
			return true;
	}
	return false;
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
