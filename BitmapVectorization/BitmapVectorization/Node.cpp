#include <iostream>
#include "Node.h"

using namespace std;

Node::Node( int a_x, int a_y )
{
	x = a_x;
	y = a_y;

	neighbors = new Coordinate*[ MAX_NEIGHBORS ];
	neighborCount = 0;

	// Set default neighbor indices to -1
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		neighbors[ i ] = new Coordinate( DEFAULT, DEFAULT );
	}

	setTraversal( false );
}

Node::~Node(void)
{
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		delete neighbors[ i ];
	}
	delete[] neighbors;
}

/**
 * Check if this node has similar YUV values to another
 */
bool Node::isSimilar( const Node* otherNode ) const
{
	float deltaY = this->color.getY() - otherNode->color.getY();
	float deltaU = this->color.getU() - otherNode->color.getU();
	float deltaV = this->color.getV() - otherNode->color.getV();

	if( deltaY < 0 )
	{
		deltaY *= -1;
	}

	if( deltaU < 0 )
	{
		deltaU *= -1;
	}

	if( deltaV < 0 )
	{
		deltaV *= -1;
	}

	bool yIsSimilar = deltaY <= maxDeltaY();
	bool uIsSimilar = deltaU <= maxDeltaU();
	bool vIsSimilar = deltaV <= maxDeltaV();

	return ( yIsSimilar && uIsSimilar && vIsSimilar );
}

/**
 * Disconnects node connections with a neighbor in a given direction
 */
void Node::severConnection( NeighborDirection direction )
{
	bool connected = ( neighbors[ direction ]->getX() >= DEFAULT ||
					   neighbors[ direction ]->getY() >= DEFAULT );

	if( connected )
	{
		neighbors[ direction ]->setX( SEVERED );
		neighbors[ direction ]->setY( SEVERED );
		
		--neighborCount;
	}
}

/**
 * Checks if a neighbor in the given direction is valid
 */
bool Node::isSevered( NeighborDirection direction ) const
{
	return neighbors[ direction ]->getX() == SEVERED ||
		   neighbors[ direction ]->getY() == SEVERED;
}

bool Node::neighborExistsAt( NeighborDirection direction ) const
{
	return neighbors[ direction ]->getX() >= 0 ||
		   neighbors[ direction ]->getY() >= 0;
}

Coordinate Node::getNextNeighbor( int offset )
{
	Coordinate severedNode( SEVERED, SEVERED );
	int neighborsChecked = 0;
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		if( *neighbors[ i ] != severedNode )
		{
			if( neighborsChecked == offset )
			{
				return Coordinate( neighbors[ i ]->getX(), neighbors[ i ]->getY() );
			}
			++neighborsChecked;
		}
	}
	return severedNode;
}

/**
 * Provides float constant representing the maximum delta Y value
 */
const float Node::maxDeltaY()
{
	return ( 48 / (float)255 );
}

/**
 * Provides float constant representing the maximum delta U value
 */
const float Node::maxDeltaU() 
{
	return ( 7 / (float)255 );
}

/**
 * Provides float constant representing the maximum delta V value
 */
const float Node::maxDeltaV() 
{
	return ( 6 / (float)255 );
}

Coordinate Node::getNeighborCoord( NeighborDirection direction )
{
	return *neighbors[ direction ];
}

void Node::setNeighbor( int neighborXOffset, int neighborYOffset, NeighborDirection direction )
{
	bool notConnected = neighbors[ direction ]->getX() < 0 || neighbors[ direction ]->getY() < 0;

	if ( !isSevered( direction ) && notConnected )
	{
		neighbors[ direction ]->setX( neighborXOffset );
		neighbors[ direction ]->setY( neighborYOffset );

		++neighborCount;
	}
}

/**
 * Gets the total amount of neighbors for this Node
 */
int Node::getNeighborCount() const
{
	return neighborCount;
}

/**
 * Gets the Color of this Node
 */
Color Node::getColor() const
{
	return color;
}

/**
 * Set the Color of this Node
 */
void Node::setColor( Color newColor )
{
	color = newColor;
}

int Node::getX()
{
	return x;
}

int Node::getY()
{
	return y;
}

bool Node::getTraversed()
{
	return traversed;
}

void Node::setTraversal( bool a_traversed )
{
	traversed = a_traversed;
}

void Node::printRgb() const
{
	cout << "R: " << color.getR() << "\tG: " << color.getG() << "\tB: " << color.getB();
}

void Node::print()
{
	/*
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		if( i == 3 || i == 5 )
		{
			cout << "\n";
		}

		if( neighbors[ i ]->getX() != Node::SEVERED )
		{
			//neighbors[ i ]->print();
			cout << "C";
		}else{
			cout << ".";
		}
		cout << " ";

		if( i == 3 )
		{
			cout << "N ";
		}
	}
	*/
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		if( i == 3 || i == 5 )
		{
			cout << "\n";
		}

		neighbors[ i ]->print();
		cout << " ";

		if( i == 3 )
		{
			cout << "X ";
		}
	}
	cout << endl << endl;
}