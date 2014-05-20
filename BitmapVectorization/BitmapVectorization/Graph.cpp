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
			pNodes[ x ][ y ] = new Node( x, y );
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
				else
				{
					pCurrentNode->severConnection( NeighborDirection( i ) );
				}
			}
		}
	}
}

void Graph::resolveCrossedConnections()
{
	const Coordinate SEVERED( Node::SEVERED, Node::SEVERED );

	for( int x = 0; x < width - 1; ++x )
	{
		for( int y = 0; y < height - 1; ++y )
		{
			Node* pCurrentNode = pNodes[ x ][ y ];
			Node* pRightNode = pNodes[ x + 1 ][ y ];

			// Check for cross
			Coordinate currentBottomRight = pCurrentNode->getNeighborCoord( NeighborDirection::BOTTOM_RIGHT );
			Coordinate rightBottomLeft = pRightNode->getNeighborCoord( NeighborDirection::BOTTOM_LEFT );

			bool topLeftToBottomRight = ( currentBottomRight != SEVERED );
			bool topRightToBottomLeft = ( rightBottomLeft != SEVERED );

			bool isCrossed = ( topLeftToBottomRight && topRightToBottomLeft );

			if( isCrossed )
			{
				Node* pBottomNode = pNodes[ x ][ y + 1 ];

				// Check for verticals and horizontals around cross
				Coordinate currentRight = pCurrentNode->getNeighborCoord( NeighborDirection::RIGHT );
				Coordinate currentBottom = pCurrentNode->getNeighborCoord( NeighborDirection::BOTTOM );
				Coordinate rightBottom = pRightNode->getNeighborCoord( NeighborDirection::BOTTOM );
				Coordinate bottomRight = pBottomNode->getNeighborCoord( NeighborDirection::RIGHT );

				bool topLeftToTopRight = ( currentRight != SEVERED );
				bool topLeftToBottomLeft = ( currentBottom != SEVERED );
				bool topRightToBottomRight = ( rightBottom != SEVERED );
				bool bottomLeftToBottomRight = ( bottomRight != SEVERED );

				bool isBoxed = ( topLeftToTopRight && topLeftToBottomLeft && topRightToBottomRight && bottomLeftToBottomRight );
				
				if( isBoxed )
				{
					Node* pBottomRightNode = pNodes[ x + 1 ][ y + 1 ];

					// Sever crossed connections
					pCurrentNode->severConnection( NeighborDirection::BOTTOM_RIGHT );
					pBottomRightNode->severConnection( NeighborDirection::TOP_LEFT );

					pRightNode->severConnection( NeighborDirection::BOTTOM_LEFT );
					pBottomNode->severConnection( NeighborDirection::TOP_RIGHT );
				}
				else
				{
					Node* pBottomRightNode = pNodes[ x + 1 ][ y + 1 ];

					// Islands heuristic
					int islandWeight = getIslandWeight( pCurrentNode, pBottomRightNode, pRightNode, pBottomNode );

					if( islandWeight < 0 )
					{
						pCurrentNode->severConnection( NeighborDirection::BOTTOM_RIGHT );
						pBottomRightNode->severConnection( NeighborDirection::TOP_LEFT );
					}
					else
					{
						pRightNode->severConnection( NeighborDirection::BOTTOM_LEFT );
						pBottomNode->severConnection( NeighborDirection::TOP_RIGHT );
					}

					/*
					// Curve heuristic
					int positiveCurveLength = traverseCurve( pCurrentNode, pBottomRightNode );
					resetCurve( pCurrentNode, pBottomRightNode );

					int negativeCurveLength = ( -1 * traverseCurve( pRightNode, pBottomNode ) );
					resetCurve( pRightNode, pBottomNode );

					int curveWeight = positiveCurveLength + negativeCurveLength;

					if( curveWeight < 0 )
					{
						pCurrentNode->severConnection( NeighborDirection::BOTTOM_RIGHT );
						pBottomRightNode->severConnection( NeighborDirection::TOP_LEFT );
					}
					else
					{
						pRightNode->severConnection( NeighborDirection::BOTTOM_LEFT );
						pBottomNode->severConnection( NeighborDirection::TOP_RIGHT );
					}
					*/
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

int Graph::traverseCurve( Node* currentNode, Node* currentNeighbor ) const
{
	int length = 0;

	if( currentNode->getNeighborCount() == 2 && !currentNode->getTraversed() )
	{
		currentNode->setTraversal( true );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = currentNode->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = currentNode->getX() + nextNeighborOffset.getX();
			int nextNeighborY = currentNode->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == currentNeighbor );
		length += traverseCurve( nextNeighbor, currentNode );
	}

	if( currentNeighbor->getNeighborCount() == 2 && !currentNeighbor->getTraversed() )
	{
		currentNeighbor->setTraversal( true );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = currentNeighbor->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = currentNeighbor->getX() + nextNeighborOffset.getX();
			int nextNeighborY = currentNeighbor->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == currentNode );
		length += traverseCurve( currentNeighbor, nextNeighbor );
	}

	return length + 1;
}

void Graph::resetCurve( Node* currentNode, Node* currentNeighbor ) const
{
	if( currentNode->getNeighborCount() == 2 && currentNode->getTraversed() )
	{
		currentNode->setTraversal( false );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = currentNode->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = currentNode->getX() + nextNeighborOffset.getX();
			int nextNeighborY = currentNode->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == currentNeighbor );

		resetCurve(nextNeighbor, currentNode );
	}

	if( currentNeighbor->getNeighborCount() == 2 && currentNeighbor->getTraversed() )
	{
		currentNeighbor->setTraversal( false );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = currentNeighbor->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = currentNeighbor->getX() + nextNeighborOffset.getX();
			int nextNeighborY = currentNeighbor->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == currentNode );
		resetCurve( currentNeighbor, nextNeighbor );
	} 
}

int Graph::getIslandWeight( Node* posCurrentNode, Node* posNeighborNode, Node* negCurrentNode, Node* negNeighborNode )
{
	int positiveWeight = 0;
	int negativeWeight = 0;

	if( posCurrentNode->getNeighborCount() == 1 )
	{
		positiveWeight += 5;
	}

	if( posNeighborNode->getNeighborCount() == 1 )
	{
		positiveWeight += 5;
	}

	if( negCurrentNode->getNeighborCount() == 1 )
	{
		negativeWeight += 5;
	}

	if( negNeighborNode->getNeighborCount() == 1 )
	{
		negativeWeight += 5;
	}

	int totalIslandWeight = positiveWeight - negativeWeight;

	return totalIslandWeight;
}