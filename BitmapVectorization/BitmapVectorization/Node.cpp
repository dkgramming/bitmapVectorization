#include "Node.h"

Node::Node(void) {}

Node::~Node(void) {}

/**
 * Check if this node has similar YUV values to another
 */
bool Node::isSimilar( const Node& otherNode )
{
	float deltaY = this->color.getY() - otherNode.color.getY();
	float deltaU = this->color.getU() - otherNode.color.getU();
	float deltaV = this->color.getV() - otherNode.color.getV();

	bool yIsSimilar = deltaY <= maxDeltaY();
	bool uIsSimilar = deltaU <= maxDeltaU();
	bool vIsSimilar = deltaV <= maxDeltaV();

	return ( yIsSimilar && uIsSimilar && vIsSimilar );
}

/**
 * Add a node to this node
 */
void Node::addNode( Node* nodeToAdd )
{
	if ( neighbors.size() < MAX_NODES )
	{
		neighbors.push_back( nodeToAdd );
	}
}

/**
 * Remove a node from this node
 */
void Node::removeNode( const Node& nodeToRemove )
{
	// Search through all nodes 
	for ( unsigned int i = 0; i < neighbors.size(); ++i )
	{
		Node* pCurrentNeighbor = neighbors[i];

		// If the node currently being checked has the
		// same memory address as the nodeToRemove,
		// remove it from our list of nodes.
		if ( pCurrentNeighbor == &nodeToRemove )
		{
			neighbors.erase( neighbors.begin() + i );
			break;
		}
	}
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

/**
 * Gets the total amount of neighbors for this Node
 */
int Node::getNeighborCount() const
{
	return neighbors.size();
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