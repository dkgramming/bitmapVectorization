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

int Graph::getHeight() const
{
	return height;
}

int Graph::getWidth() const
{
	return width;
}

Node* Graph::getNodeAt( int a_x, int a_y ) const
{
	return pNodes[ a_x ][ a_y ];
}

/**
 * Iterates through graph and tells each node to sever its dissimilar neighbors
 */
void Graph::severDissimilarNodes()
{
	for( int x = 0; x < width; ++x )
	{
		for( int y = 0; y < height; ++y )
		{
			severDissimilarNeighbors( x, y );
		}
	}
}

/**
 * Iterates through neighbors and severs connections to dissimilar ones
 */
void Graph::severDissimilarNeighbors( int a_x, int a_y )
{
	Node* pCurrentNode = pNodes[ a_x ][ a_y ];

	for( int i = 0; i < Node::MAX_NEIGHBORS; ++i )
	{
		Coordinate currentOffset = getOffsetAt( NeighborDirection( i ) );
		int neighborX = ( a_x + currentOffset.getX() );
		int neighborY = ( a_y + currentOffset.getY() );

		bool nonNegative = ( neighborX >= 0 && neighborY >= 0 );
		bool inRange = ( neighborX < getWidth() && neighborY < getHeight() );

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

/**
 * Removes overlapping connections in order to 'flatten', i.e. make it planar
 *
 *	TODO: REFACTOR THIS!
 */
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

					// Sparseness heuristic
					int sparsenessVote = getSparsenessVote( pCurrentNode, pRightNode );
					const float SPARSENESS_WEIGHT = -0.5f;

					// Islands heuristic
					int islandVote = getIslandVote( pCurrentNode, pBottomRightNode, pRightNode, pBottomNode );
					const float ISLAND_WEIGHT = 5;

					// Curve heuristic
					int curveVote = getCurveVote( pCurrentNode, pBottomRightNode, pRightNode, pBottomNode );
					const float CURVE_WEIGHT = 0.5f;

					float weightedVote = ( sparsenessVote * SPARSENESS_WEIGHT ) +
									   ( islandVote * ISLAND_WEIGHT ) +
									   ( curveVote * CURVE_WEIGHT );

					if( weightedVote >= 0 )
					{
						pRightNode->severConnection( NeighborDirection::BOTTOM_LEFT );
						pBottomNode->severConnection( NeighborDirection::TOP_RIGHT );
					}
					else
					{
						pCurrentNode->severConnection( NeighborDirection::BOTTOM_RIGHT );
						pBottomRightNode->severConnection( NeighborDirection::TOP_LEFT );
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

/**
 * Recursively calculates the length of a segment of a curve
 */
int Graph::getBranchLength( Node* a_pOrigin, Node* a_pCross ) const
{
	if( a_pOrigin->getNeighborCount() == 2 && !a_pOrigin->getTraversed() )
	{
		a_pOrigin->setTraversal( true );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = a_pOrigin->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = a_pOrigin->getX() + nextNeighborOffset.getX();
			int nextNeighborY = a_pOrigin->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == a_pCross );

		return 1 + getBranchLength( nextNeighbor, a_pOrigin );
	}
	a_pOrigin->setTraversal( true );
	return 0;
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
 * Prints a representation of the graph using each of the nodes' neighbor count
 */
void Graph::print() const
{
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
	cout << endl;
}

/**
 * Recursively traverses a 'curve' in the graph and determines its length
 *
 * TODO: Come up with a more appropriate name
 */
int Graph::traverseCurve( Node* a_pCurrentNode, Node* a_pCurrentNeighbor ) const
{
	int length = 0;

	int firstLength = getBranchLength( a_pCurrentNode, a_pCurrentNeighbor );
	int secondLength = getBranchLength( a_pCurrentNeighbor, a_pCurrentNode );

	resetCurve( a_pCurrentNode, a_pCurrentNeighbor );

	length = firstLength + secondLength;

	return length + 1;
}

/**
 * Recursively traverses a 'curve' in the graph and resets the traveresed variable to false
 *
 * TODO: Come up with a more appropriate name
 */
void Graph::resetCurve( Node* a_pCurrentNode, Node* a_pCurrentNeighbor ) const
{
	if( a_pCurrentNode->getNeighborCount() == 2 && a_pCurrentNode->getTraversed() )
	{
		a_pCurrentNode->setTraversal( false );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = a_pCurrentNode->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = a_pCurrentNode->getX() + nextNeighborOffset.getX();
			int nextNeighborY = a_pCurrentNode->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == a_pCurrentNeighbor );

		resetCurve(nextNeighbor, a_pCurrentNode );
	}

	if( a_pCurrentNeighbor->getNeighborCount() == 2 && a_pCurrentNeighbor->getTraversed() )
	{
		a_pCurrentNeighbor->setTraversal( false );

		int nextOffsetIndex = 0;
		Coordinate nextNeighborOffset;
		Node* nextNeighbor;

		do
		{
			nextNeighborOffset = a_pCurrentNeighbor->getNextNeighbor( nextOffsetIndex );
			int nextNeighborX = a_pCurrentNeighbor->getX() + nextNeighborOffset.getX();
			int nextNeighborY = a_pCurrentNeighbor->getY() + nextNeighborOffset.getY();
			nextNeighbor = pNodes[ nextNeighborX ][ nextNeighborY ];
			++nextOffsetIndex;
		}
		while( nextNeighbor == a_pCurrentNode );
		resetCurve( a_pCurrentNeighbor, nextNeighbor );
	}
}

/**
 * Calculates the weight associated with the island heuristic
 */
int Graph::getIslandVote( Node* a_pPosCurrentNode, Node* a_pPosNeighborNode, Node* a_pNegCurrentNode, Node* a_pNegNeighborNode )
{
	int positiveVote = 0;
	int negativeVote = 0;

	if( a_pPosCurrentNode->getNeighborCount() == 1 )
	{
		positiveVote += 1;
	}

	if( a_pPosNeighborNode->getNeighborCount() == 1 )
	{
		positiveVote += 1;
	}

	if( a_pNegCurrentNode->getNeighborCount() == 1 )
	{
		negativeVote += 1;
	}

	if( a_pNegNeighborNode->getNeighborCount() == 1 )
	{
		negativeVote += 1;
	}

	int islandVote = positiveVote - negativeVote;

	return islandVote;
}

/**
 * Calculates the weight associated with the sparseness heuristic
 */
int Graph::getSparsenessVote( Node* a_pCurrentNode, Node* a_pNeighborNode )
{
	const int currentX = a_pCurrentNode->getX();
	const int currentY = a_pCurrentNode->getY();

	int positiveVote = 0;
	int negativeVote = 0;


	const int INITIAL_X = ( currentX - 1 >= 0 ) ? currentX - 1 : 0;
	const int INITIAL_Y = ( currentY - 1 >= 0 ) ? currentY - 1 : 0;
	const int X_MAX = ( currentX + 2 < width ) ? currentX + 2 : width - 1;
	const int Y_MAX = ( currentY + 2 < height ) ? currentY + 2 : height - 1;

	for( int x = INITIAL_X; x <= X_MAX; ++x )
	{
		for( int y = INITIAL_Y; y <= Y_MAX; ++y )
		{
			Node* nodeToCheck = pNodes[ x ][ y ];

			if( a_pCurrentNode->isSimilar( nodeToCheck ) )
			{
				++positiveVote;
			}
			
			if( a_pNeighborNode->isSimilar( nodeToCheck ) )
			{
				++negativeVote;
			}
		}
	}

	int sparsenessVote = negativeVote - positiveVote;
	
	return sparsenessVote;
}

int Graph::getCurveVote( Node* a_pPosCurrentNode, Node* a_pPosNeighborNode, Node* a_pNegCurrentNode, Node* a_pNegNeighborNode )
{
	int positiveCurveLength = traverseCurve( a_pPosCurrentNode, a_pPosNeighborNode );

	int negativeCurveLength = traverseCurve( a_pNegCurrentNode, a_pNegNeighborNode );

	int curveVote = positiveCurveLength - negativeCurveLength;

	return curveVote;
}