/*
	Ong, Johnny
	Ngo, Simon
	Yang, Glen

	March 14, 2020

	CS A200
	Lab 2
*/

#include "Graph.h"
#include <iostream>
#include <queue>
using namespace std;

// Default constructor
Graph::Graph()
{
	numOfVertices = 0;
	maxVertices = MAX_MATRIX_VERTICES;

	vertices = new string[maxVertices];

	matrix = new int* [maxVertices];
	for (int i = 0; i < maxVertices; ++i)
		matrix[i] = new int[maxVertices] {0};
}

// Overloaded constructor
Graph::Graph(int totalVertices)
{
	// Your code here...
	numOfVertices = totalVertices;
	maxVertices = MAX_MATRIX_VERTICES;

	vertices = new string[maxVertices];

	matrix = new int* [maxVertices];
	for (int i = 0; i < maxVertices; i++)
	{
		matrix[i] = new int[maxVertices] {0};
	}
}

Graph::Graph(const Graph& otherGraph)
{
	numOfVertices = otherGraph.numOfVertices;
	maxVertices = otherGraph.maxVertices;

	vertices = new string[maxVertices];
	for (int i = 0; i < maxVertices; i++)
	{
		vertices[i] = otherGraph.vertices[i];
	}

	matrix = new int* [maxVertices];
	for (int i = 0; i < maxVertices; i++)
	{
		matrix[i] = new int[maxVertices] {0};
	}

	for (int i = 0; i < numOfVertices; i++)
	{
		for (int j = 0; j < numOfVertices; j++)
		{
			matrix[i][j] = otherGraph.matrix[i][j];
		}
	}
}

Graph& Graph::operator=(const Graph& otherGraph)
{
	if (this == &otherGraph)
	{
		cerr << "Attempted assignment to self" << endl;
	}
	else
	{
		numOfVertices = otherGraph.numOfVertices;
		this->~Graph();
		numOfVertices = otherGraph.numOfVertices;
		maxVertices = otherGraph.maxVertices;

		vertices = new string[maxVertices];
		for (int i = 0; i < maxVertices; i++)
		{
			vertices[i] = otherGraph.vertices[i];
		}

		matrix = new int* [maxVertices];
		for (int i = 0; i < maxVertices; i++)
		{
			matrix[i] = new int[maxVertices] {0};
		}

		for (int i = 0; i < numOfVertices; i++)
		{
			for (int j = 0; j < numOfVertices; j++)
			{
				matrix[i][j] = otherGraph.matrix[i][j];
			}
		}
	}
	return *this;
}

// createGraph
void Graph::createGraph(const vector<vector<int>>& graphData,
	const vector<string>& labels)
{
	// Your code here...
	numOfVertices = static_cast<int>(labels.size());
	for (int i = 0; i < numOfVertices; i++)
	{
		vertices[i] = labels[i];
	}

	{
		for (int i = 0; i < numOfVertices; i++)
		{
			for (int j = 0; j < numOfVertices; j++)
			{
				matrix[i][j] = graphData[i][j];
			}
		}
	}

}

// printVertices
// Assume the list has at least one vertex.
void Graph::printVertices() const
{
	// Your code here...
	for (int i = 0; i < numOfVertices; i++)
	{
		cout << vertices[i] << " ";
	}
}

// printAdjacentVertices
// Assume the list has at least at least one vertex.
// Assume the vertex is somewhere in the list.
// Assume there is at least one adjacency.
void Graph::printAdjacentVertices(const string& vertex) const
{
	// Your code here...
	bool stateFound = false;
	int stateIdx = 0;
	while (!stateFound)
	{
		if (vertex == vertices[stateIdx])
		{
			stateFound = true;
		}
		else
		{
			stateIdx++;
		}
	}

	cout << vertex << ": ";
	for (int i = 0; i < numOfVertices; i++)
	{
		if (matrix[stateIdx][i] == 1)
		{
			cout << vertices[i] << " ";
		}
	}
	cout << endl;
}

//printBFS
void Graph::printBFS(const string& vertex) const
{
	// Your code here...
	queue<string> visitedQueue;
	queue<string> finalQueue;
	int visitedCheck[MAX_MATRIX_VERTICES] = { 0 };
	string currentState = vertex;
	visitedQueue.push(vertex);

	int nodeCounter = 1;
	while (nodeCounter < numOfVertices)
	{
		bool stateFound = false;
		int stateIdx = 0;
		while (!stateFound)
		{
			if (currentState == vertices[stateIdx])
			{
				stateFound = true;
			}
			else
			{
				stateIdx++;
			}
		}
		visitedCheck[stateIdx]++;

		for (int i = 0; i < numOfVertices; i++)
		{
			if (matrix[stateIdx][i] == 1 && visitedCheck[i] < 1)
			{
				visitedQueue.push(vertices[i]);
				visitedCheck[i]++;
				nodeCounter++;
			}
		}
		finalQueue.push(visitedQueue.front());
		visitedQueue.pop();
		currentState = visitedQueue.front();
	}

	cout << "Starting Vertex: " << vertex << endl;

	while (!visitedQueue.empty())
	{
		finalQueue.push(visitedQueue.front());
		visitedQueue.pop();
	}

	while (!finalQueue.empty())
	{
		cout << finalQueue.front() << " ";
		finalQueue.pop();
	}
	cout << endl;
}

// destructor
Graph::~Graph()
{
	// Your code here...
	destroyGraph();
	delete[] vertices;
	delete[] matrix;
	vertices = nullptr;
	matrix = nullptr;
}

void Graph::destroyGraph()
{
	for (int i = 0; i < numOfVertices; i++)
	{
		delete[] matrix[i];
	}
}

void Graph::modifyForTesting()
{
	// To view arrays in debugger:
	// vertices, 4
	// matrix[0],4
	// matrix[1],4
	// ...

	// Cannot modify vertices, because the main
	// function uses the vector with labels
	// Bill and Cinderella befriended
	matrix[0][1] = 1;
	matrix[1][0] = 1;
}

Graph::Graph(Graph&& otherGraph) noexcept
{
	numOfVertices = otherGraph.numOfVertices;
	maxVertices = otherGraph.maxVertices;
	vertices = otherGraph.vertices;
	matrix = otherGraph.matrix;

	otherGraph.numOfVertices = 0;
	otherGraph.maxVertices = 0;
	otherGraph.vertices = nullptr;
	otherGraph.matrix = nullptr;
}

Graph& Graph::operator=(Graph&& otherGraph) noexcept
{
	if (this == &otherGraph)
	{
		cerr << "Attempted assignment to self" << endl;
	}
	else
	{
		this->~Graph();
		numOfVertices = otherGraph.numOfVertices;
		maxVertices = otherGraph.maxVertices;
		vertices = otherGraph.vertices;
		matrix = otherGraph.matrix;

		otherGraph.numOfVertices = 0;
		otherGraph.maxVertices = 0;
		otherGraph.vertices = nullptr;
		otherGraph.matrix = nullptr;
	}
	return *this;
}