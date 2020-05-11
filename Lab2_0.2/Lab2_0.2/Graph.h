/*
	Ong, Johnny
	Ngo, Simon
	Yang, Glen

	March 14, 2020

	CS A200
	Lab 2
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

const int MAX_MATRIX_VERTICES = 10;

class Graph
{
public:
	Graph();
	Graph(int totalVertices);
	Graph(const Graph& otherGraph);
	Graph(Graph&&) noexcept;
	Graph& operator=(Graph&&) noexcept;
	Graph& operator=(const Graph&);

	void createGraph(const std::vector<std::vector<int>>& graphData,
		const std::vector<std::string>& labels);

	void printVertices() const;
	void printAdjacentVertices(const std::string& vertex) const;
	void printBFS(const std::string& vertex) const;

	void modifyForTesting();

	~Graph();
	void destroyGraph();

private:

	std::string* vertices;	//will point to a dynamic array storing labels for vertices
	int** matrix;			//will point to a dynamic array of pointers to dynamic arrays
	int maxVertices;		//max number of vertices the graph can hold (capacity)
	int numOfVertices;		//total number of vertices
};

#endif 