#include "Graph.h"

Graph::Graph( int a_numColumns, int a_numRows )
{
	numRows = a_numRows;
	numColumns = a_numColumns;

	// Create all the nodes for the graph
	pNodes = new Node*[ numRows * numColumns ];

	for( int i = 0; i < numRows * numColumns; ++i )
	{
		pNodes[ i ] = new Node();
	}
}


Graph::~Graph(void)
{
	// Delete each column
	for( int i = 0; i < numRows * numColumns; ++i )
	{
		delete pNodes[ i ];
	}

	// Delete all the rows
	delete[] pNodes;
}

void Graph::setColorAtNode( int a_index, int a_r, int a_g, int a_b )
{
	Color newColor;
	newColor.setRGB( a_r, a_g, a_b );
	pNodes[ a_index ]->setColor( newColor );
}

void Graph::printRgbAtNode( int a_index )
{
	pNodes[ a_index ]->printRgb();
}

int Graph::getNumRows() const
{
	return numRows;
}

int Graph::getNumCols() const
{
	return numColumns;
}