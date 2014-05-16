#include "Graph.h"

Graph::Graph( int a_numColumns, int a_numRows )
{
	numRows = a_numRows;
	numColumns = a_numColumns;

	// Create all the nodes for the graph
	pNodes = new Node**[ numColumns ];

	for( int x = 0; x < numColumns; ++x )
	{
		pNodes[ x ] = new Node*[ numRows ];

		for( int y = 0; y < numRows; ++y )
		{
			pNodes[ x ][ y ] = new Node();
		}
	}
}


Graph::~Graph(void)
{
	// Delete each row
	for( int x = 0; x < numColumns; ++x )
	{
		for( int y = 0; y < numRows; ++y )
		{
			delete pNodes[ x ][ y ];
		}

		delete[] pNodes[ x ];
	}

	// Delete all the columns
	delete[] pNodes;
}

void Graph::setColorAtNode( int a_x, int a_y, int a_r, int a_g, int a_b )
{
	Color newColor;
	newColor.setRGB( a_r, a_g, a_b );
	pNodes[ a_x ][ a_y ]->setColor( newColor );
}

void Graph::printRgbAtNode( int a_x, int a_y )
{
	pNodes[ a_x ][ a_y ]->printRgb();
}

int Graph::getNumRows() const
{
	return numRows;
}

int Graph::getNumCols() const
{
	return numColumns;
}