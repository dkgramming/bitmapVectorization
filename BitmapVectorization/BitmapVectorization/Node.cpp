#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(void)
{
	// Set default neighbor indices to -1
	for( int i = 0; i < MAX_NODES; ++i )
	{
		neighbors[ i ] = new Coordinate( -1, -1 );
	}
}

Node::~Node(void)
{
	for( int i = 0; i < MAX_NODES; ++i )
	{
		delete neighbors[ i ];
	}
}

/**
 * Check if this node has similar YUV values to another
 */
bool Node::isSimilar( const Node& otherNode )
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
 * Disconnects node connections with a neighbor
 */
void Node::severConnection( NeighborDirection direction )
{
	neighbors[ direction ]->setX( -1 );
	neighbors[ direction ]->setY( -1 );
}

/**
 * Provides float constant representing the maximum delta Y value
 */
const float Node::maxDeltaY()
{
	return 48 / (float)255;
}

/**
 * Provides float constant representing the maximum delta U value
 */
const float Node::maxDeltaU() 
{
	return 7 / (float)255;
}

/**
 * Provides float constant representing the maximum delta V value
 */
const float Node::maxDeltaV() 
{
	return 6 / (float)255;
}

Coordinate Node::getNeighborCoord( NeighborDirection direction )
{
	return *neighbors[ direction ];
}

void Node::setNeighbor( int graphNeighborXIndex, int graphNeighborYIndex, NeighborDirection direction )
{
	neighbors[ direction ]->setX( graphNeighborXIndex );
	neighbors[ direction ]->setY( graphNeighborYIndex );
}

/**
 * Gets the total amount of neighbors for this Node
 */
int Node::getNeighborCount() const
{
	int size = 0;

	for( int i = 0; i < MAX_NODES; ++i )
	{
		if( neighbors[ i ]->getX() != -1 || neighbors[ i ]->getY() != -1 )
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