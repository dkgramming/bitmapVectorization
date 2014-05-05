#include "Graph.h"

Graph::Graph( int a_numRows, int a_numColumns )
{
	numRows = a_numRows;
	numColumns = a_numColumns;

	// Create all the nodes for the graph,
	// starting by creating all the rows
	nodes = new Node*[numRows];

	// Create the columns for each row
	for ( int i = 0; i < numRows; ++i )
	{
		nodes[i] = new Node[numColumns];
	}
}


Graph::~Graph(void)
{
	// Delete each column
	for ( int i = 0; i < numRows; ++i )
	{
		delete[] nodes[i];
	}

	// Delete all the rows
	delete[] nodes;
}
