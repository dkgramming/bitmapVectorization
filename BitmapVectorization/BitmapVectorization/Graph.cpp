#include "Graph.h"

Graph::Graph( RawImage a_image )
{
	numRows = a_image.getHeight();
	numColumns = a_image.getWidth();

	// Create all the nodes for the graph,
	// starting by creating all the rows
	nodes = new Node*[numRows];

	// Create the columns for each row
	for ( int i = 0; i < numRows; ++i )
	{
		nodes[i] = new Node[numColumns];
	}

	setNodeColors( a_image );
}


Graph::~Graph(void)
{
	// Delete each column
	for( int i = 0; i < numRows; ++i )
	{
		delete[] nodes[i];
	}

	// Delete all the rows
	delete[] nodes;
}

void Graph::setNodeColors( const RawImage& image )
{
	Color** pixelData = image.getPixelData();

	for( int rowIndex = 0; rowIndex < numRows; ++rowIndex )
	{
		for( int columnIndex = 0; columnIndex < numColumns; ++columnIndex )
		{
			Color color( *pixelData[ columnIndex + ( rowIndex * numColumns ) ] );
			nodes[ columnIndex ][ rowIndex ].setColor( color ); 
		}
	}
}