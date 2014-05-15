#include "Graph.h"

Graph::Graph( RawImage a_image )
{
	numRows = a_image.getHeight();
	numColumns = a_image.getWidth();

	// Create all the nodes for the graph,
	// starting by creating all the rows
	pNodes = new Node*[ numRows * numColumns];

	//setNodeColors( a_image );
}


Graph::~Graph(void)
{
	// Delete each column
	for( int i = 0; i < numRows * numColumns; ++i )
	{
		delete pNodes[i];
	}

	// Delete all the rows
	delete[] pNodes;
}

void Graph::setColorAtNode( int a_index, int a_r, int a_g, int a_b )
{
	Color newColor( a_r, a_g, a_b );
	pNodes[ a_index ]->setColor( newColor );
}

int Graph::getNumRows() const
{
	return numRows;
}

int Graph::getNumCols() const
{
	return numColumns;
}