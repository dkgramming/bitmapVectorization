#include "Graph.h"
#include "Coordinate.h"

Graph::Graph( int a_numColumns, int a_numRows )
{
	height = a_numRows;
	width = a_numColumns;

	// Create all the nodes for the graph
	pNodes = new Node**[ width ];

	for( int x = 0; x < width; ++x )
	{
		pNodes[ x ] = new Node*[ height ];

		for( int y = 0; y < height; ++y )
		{
			pNodes[ x ][ y ] = new Node();
		}
	}

	// Connect all nodes
	connectNodes();
}


Graph::~Graph(void)
{
	// Delete each row
	for( int x = 0; x < width; ++x )
	{
		for( int y = 0; y < height; ++y )
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
	return height;
}

int Graph::getNumCols() const
{
	return width;
}

void Graph::severDissimilarNodes()
{
	for( int x = 0; x < width; ++x )
	{
		for( int y = 0; y < height; ++y )
		{
			Node* pCurrentNode = pNodes[ x ][ y ];

			for( int i = 0; i < Node::MAX_NEIGHBORS; ++i )
			{
				Coordinate currentOffset = getOffsetAt( NeighborDirection( i ) );
				int neighborX = ( x + currentOffset.getX() );
				int neighborY = ( y + currentOffset.getY() );

				bool nonNegative = ( neighborX >= 0 && neighborY >= 0 );
				bool inRange = ( neighborX < getNumCols() && neighborY < getNumRows() );

				if( nonNegative && inRange )
				{
					bool isSimilar = pCurrentNode->isSimilar( pNodes[ neighborX ][ neighborY ] );
					
					if( !isSimilar )
					{
						pCurrentNode->severConnection( NeighborDirection( i ) );
					}
				}
			}
		}
	}
}

void Graph::connectNodes()
{
	for( int x = 0; x < width; ++x )
	{
		for( int y = 0; y < height; ++y )
		{
			Node* pCurrentNode = pNodes[ x ][ y ];
			markInvalidNeighbors( *pCurrentNode, x, y );

			for( int i = 0; i < Node::MAX_NEIGHBORS; ++i )
			{
				Coordinate currentOffset = getOffsetAt( NeighborDirection( i ) );
				pCurrentNode->setNeighbor( currentOffset.getX(),
										   currentOffset.getY(),
										   NeighborDirection( i ) );
			}
		}
	}
}

// TODO: Make this more static
const Coordinate Graph::getOffsetAt( NeighborDirection a_direction ) const
{
	const Coordinate TOP_LEFT_OFFSET( -1, -1 );
	const Coordinate TOP_OFFSET( 0, -1 );
	const Coordinate TOP_RIGHT_OFFSET( 1, -1 );
	const Coordinate LEFT_OFFSET( -1, 0 );
	const Coordinate RIGHT_OFFSET( 1, 0 );
	const Coordinate BOTTOM_LEFT_OFFSET( -1, 1 );
	const Coordinate BOTTOM_OFFSET( 0, 1 );
	const Coordinate BOTTOM_RIGHT_OFFSET( 1, 1 );
	
	const Coordinate OFFSETS[ Node::MAX_NEIGHBORS ] =
	{
		TOP_LEFT_OFFSET,
		TOP_OFFSET,
		TOP_RIGHT_OFFSET,
		LEFT_OFFSET,
		RIGHT_OFFSET,
		BOTTOM_LEFT_OFFSET,
		BOTTOM_OFFSET,
		BOTTOM_RIGHT_OFFSET,
	};

	return OFFSETS[ a_direction ];
}

bool Graph::isOnTop( int y ) const 
{ 
	return ( y == 0 ); 
}

bool Graph::isOnBottom( int y ) const 
{ 
	return ( y == ( height - 1 ) ); 
}

bool Graph::isOnLeft( int x ) const 
{ 
	return ( x == 0 ); 
}

bool Graph::isOnRight( int x ) const 
{ 
	return ( x == ( width - 1 ) ); 
}

/**
 * Confirms invalid nodes for positions off the graph
 */
void Graph::markInvalidNeighbors( Node& currentNode, int x, int y )
{
	if( isOnTop( y ) )
	{
		currentNode.severConnection( NeighborDirection::TOP_LEFT );
		currentNode.severConnection( NeighborDirection::TOP );
		currentNode.severConnection( NeighborDirection::TOP_RIGHT );
	}

	if( isOnBottom( y ) )
	{
		currentNode.severConnection( NeighborDirection::BOTTOM_LEFT );
		currentNode.severConnection( NeighborDirection::BOTTOM );
		currentNode.severConnection( NeighborDirection::BOTTOM_RIGHT );
	}

	if( isOnLeft( x ) )
	{
		currentNode.severConnection( NeighborDirection::TOP_LEFT );
		currentNode.severConnection( NeighborDirection::LEFT );
		currentNode.severConnection( NeighborDirection::BOTTOM_LEFT );
	}

	if( isOnRight( x ) )
	{
		currentNode.severConnection( NeighborDirection::TOP_RIGHT );
		currentNode.severConnection( NeighborDirection::RIGHT );
		currentNode.severConnection( NeighborDirection::BOTTOM_RIGHT );
	}
}

void Graph::print() const
{
	char input;
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			Node* pCurrentNode = pNodes[ x ][ y ];
			cout << pCurrentNode->getNeighborCount();
			cout << " ";
		}
		cout << endl;
	}
	cin >> input;
}