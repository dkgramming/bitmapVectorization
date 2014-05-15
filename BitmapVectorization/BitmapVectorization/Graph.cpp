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

void Graph::setNodeColors( const RawImage& image )
{
	Color** pixelData = image.getPixelData();

	for( int index = 0; index < numRows * numColumns; ++index )
	{
		pNodes[ index ]->setColor( *pixelData[ index ] );
	}
}

int Graph::getNumRows() const
{
	return numRows;
}

int Graph::getNumCols() const
{
	return numColumns;
}