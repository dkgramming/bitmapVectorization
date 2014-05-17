#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(void)
{
	neighbors = new Coordinate*[ MAX_NEIGHBORS ];

	// Set default neighbor indices to -1
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		neighbors[ i ] = new Coordinate( -1, -1 );
	}
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
bool Node::isSimilar( const Node& otherNode ) const
{
	float deltaY = this->color.getY() - otherNode.color.getY();
	float deltaU = this->color.getU() - otherNode.color.getU();
	float deltaV = this->color.getV() - otherNode.color.getV();

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
	neighbors[ direction ]->setX( -1 );
	neighbors[ direction ]->setY( -1 );
}

/**
 * Confirms that a node has no connections in a given direction
 */
void Node::invalidate( NeighborDirection direction )
{
	neighbors[ direction ]->setX( INVALID );
	neighbors[ direction ]->setY( INVALID );
}

/**
 * Checks if a neighbor in the given direction is valid
 */
bool Node::isValid( NeighborDirection direction ) const
{
	return neighbors[ direction ]->getX() != INVALID ||
		   neighbors[ direction ]->getY() != INVALID;
}

bool Node::neighborExistsAt( NeighborDirection direction ) const
{
	return neighbors[ direction ]->getX() >= 0 ||
		   neighbors[ direction ]->getY() >= 0;
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

void Node::setNeighbor( int graphNeighborXIndex, int graphNeighborYIndex, NeighborDirection direction )
{
	if ( isValid( direction ) )
	{
		neighbors[ direction ]->setX( graphNeighborXIndex );
		neighbors[ direction ]->setY( graphNeighborYIndex );
	}
}

/**
 * Gets the total amount of neighbors for this Node
 */
int Node::getNeighborCount() const
{
	int size = 0;

	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		if( neighborExistsAt( NeighborDirection( i ) ) )
		{
			++size;
		}
	}

	return size;
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

void Node::printRgb() const
{
	cout << "R: " << color.getR() << "\tG: " << color.getG() << "\tB: " << color.getB() << endl;
}

void Node::print()
{
	for( int i = 0; i < MAX_NEIGHBORS; ++i )
	{
		if( i == 3 || i == 5 )
		{
			cout << "\n";
		}

		neighbors[ i ]->print();
		cout << "\t";

		if( i == 3 )
		{
			cout << "\t\t";
		}
	}
	cout << endl << endl;
}