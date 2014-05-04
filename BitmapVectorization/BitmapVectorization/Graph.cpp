#include "Graph.h"

Graph::Graph( int numRows, int numColumns )
{
	this->numRows = numRows;
	this->numColumns = numColumns;

	// Create all the nodes for the graph,
	// starting by creating all the rows
	nodes = new Node*[numRows];

	// Create the columns for each row
	for ( int i = 0; i < numRows; ++i )
		nodes[i] = new Node[numColumns];
}


Graph::~Graph(void)
{
	// Delete each column
	for ( int i = 0; i < numRows; ++i )
		delete[] nodes[i];

	// Delete all the rows
	delete[] nodes;
}
