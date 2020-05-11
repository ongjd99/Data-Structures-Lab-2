/*
	Ong, Johnny
	Ngo, Simon
	Yang, Glen

	March 14, 2020

	CS A200
	Lab 2
*/

#include "Graph.h"

#include <vector>
#include <string>

using namespace std;

void print(const Graph& graph, const vector<string>& states);
void setUpGraph(const vector<string>& states,
	const vector<vector<int>>& neighbors, Graph& graph);

int main()
{
	vector<string> states = {
		//0.............1...........2...
		"Arizona", "California", "Oregon" };

	vector<vector<int>> neighbors = {
		//0, 1, 2, 3
		{ 0, 1, 0, 0 },  //0 Arizona
		{ 1, 0, 1, 0 },  //1 California
		{ 0, 1, 0, 0 },  //2 Oregon	
		{ 0, 0, 0, 0 },  //3

	};

	Graph graph(4);
	graph.createGraph(neighbors, states);
	cout << "STATES: ";
	graph.printVertices();

	cout << "\nNEIGHBORS\n";
	for (const string& i : states)
		graph.printAdjacentVertices(i);
	cout << endl;

	/*******************************************
	* TEST: Copy constructor
	*******************************************/
	{
		cout << "\nTEST: Copy constructor\n";
		Graph graph(4);
		setUpGraph(states, neighbors, graph);
		cout << "\nCreate new graph: Graph newGraph(graph);\n";
		Graph newGraph(graph);
		cout << "\nPrint old graph...\n";
		print(graph, states);
		cout << "\nPrint new graph...\n";
		print(newGraph, states);
		cout << "\nModify old graph...\n";
		graph.modifyForTesting();
		cout << "\nPrint old graph (should have been modified)...\n";
		print(graph, states);
		cout << "\nPrint new graph (should not have been modified)...\n";
		print(newGraph, states);
	}

	cout << "\n=============================================\n";

	/*******************************************
	* TEST: Move constructor
	* Note that there are two statements at the
	* end of this section that will crash the
	* program. Uncomment them to check it it
	* does so.
	*******************************************/
	{
		cout << "\nTEST: Move constructor\n";
		Graph graph(4);
		setUpGraph(states, neighbors, graph);
		cout << "\nCreate new graph: Graph newGraph = move(graph);\n";
		Graph newGraph = move(graph);
		cout << "\nPrint new graph...\n";
		print(newGraph, states);
		//cout << "\nPrint old graph...\n"; // should crash the program
		//print(graph, states);
	}

	cout << "\n=============================================\n";

	/*******************************************
	* TEST: Overloaded assignment operator
	*******************************************/
	{
		cout << "\nTEST: Overloaded assignment constructor\n";
		Graph graph(4);
		setUpGraph(states, neighbors, graph);
		// Need to create a different graph
		vector<string> newStates = {
			//0.............1...........2...........3......4...
			"Arizona", "California", "Oregon", "Utah", "Washington" };
		vector<vector<int>> newNeighbors = {
			//0, 1, 2, 3, 4
			{ 0, 1, 0, 1, 0 },  //0 Arizona
			{ 1, 0, 1, 0, 0 },  //1 California
			{ 0, 1, 0, 0, 1 },  //2 Oregon	
			{ 1, 0, 0, 0, 0 },  //3 Utah
		  { 0, 0, 1, 0, 0 },	//4 Washington
		};
		cout << "\nCreate new graph: Graph newGraph(graph);\n";
		Graph newGraph(5);
		newGraph.createGraph(newNeighbors, newStates);
		cout << "\nPrint old graph...\n";
		print(graph, states);
		cout << "\nPrint new graph...\n";
		print(newGraph, newStates);
		cout << "\nCopy old graph into new graph...\n";
		newGraph = graph;
		cout << "\nPrint old graph...\n";
		print(graph, states);
		cout << "\nPrint new graph...\n";
		print(newGraph, states);
		cout << "\nModify old graph...\n";
		graph.modifyForTesting();
		cout << "\nPrint old graph (should have been modified)...\n";
		print(graph, states);
		cout << "\nPrint new graph (should not have been modified)...\n";
		print(newGraph, states);
	}

	cout << "\n=============================================\n";

	/*******************************************
	* TEST: Move assignment operator
	* Note that there are two statements at the
	* end of this section that will crash the
	* program. Uncomment them to check it it
	* does so.
	*******************************************/
	{
		cout << "\nTEST: Move assignment constructor\n";
		Graph graph(4);
		setUpGraph(states, neighbors, graph);
		// Need to create a different graph
		vector<string> newStates = {
			//0.........1............2.......3.......4.....
			"Bill", "Cinderella", "Jane", "Mindy", "Lana" };
		vector<vector<int>> newNeighbors = {
			//0, 1, 2, 3, 4
			{ 0, 0, 1, 0, 1 },  //0 Bill
			{ 0, 0, 1, 1, 1 },  //1 Cinderella
			{ 1, 1, 0, 0, 0 },  //2 Jane	
			{ 0, 0, 0, 0, 1 },  //3 Mindy
			{ 1, 0, 0, 1, 0 },  //4 Lana
		};
		cout << "\nCreate new graph: Graph newGraph(graph);\n";
		Graph newGraph(5);
		newGraph.createGraph(newNeighbors, newStates);
		cout << "\nPrint old graph...\n";
		print(graph, states);
		cout << "\nPrint new graph...\n";
		print(newGraph, newStates);
		cout << "\nMove old graph into new graph...\n";
		newGraph = move(graph);
		cout << "\nPrint new graph...\n";
		print(newGraph, states);
		//cout << "\nPrint old graph...\n"; // should crash the program
		//print(graph, states);
	}

	cout << endl;
	system("Pause");
	return 0;
}

void print(const Graph& graph, const vector<string>& states)
{
	cout << "STATES: ";
	graph.printVertices();

	cout << "\nNEIGHBORS\n";
	for (const string& i : states)
		graph.printAdjacentVertices(i);
}

void setUpGraph(const vector<string>& states,
	const vector<vector<int>>& neighbors, Graph& graph)
{
	graph.createGraph(neighbors, states);
	cout << "MEMBERS: ";
	graph.printVertices();

	cout << "\nFRIENDS\n";
	for (const string& i : states)
		graph.printAdjacentVertices(i);
}