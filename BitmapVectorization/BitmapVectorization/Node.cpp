#include "Node.h"

Node::Node(void) {}

Node::~Node(void) {}

/**
 * @TODO
 * Check if this node has similar YUV values to another
 */
bool Node::isSimilar( const Node& otherNode )
{
	float deltaY = this->color.getY() - otherNode.color.getY();
	float deltaU = this->color.getU() - otherNode.color.getU();
	float deltaV = this->color.getV() - otherNode.color.getV();

	bool yIsSimilar = deltaY <= (float)MAX_DELTA_Y/(float)DELTA_DENOMINATOR;
	bool uIsSimilar = deltaU <= (float)MAX_DELTA_U/(float)DELTA_DENOMINATOR;
	bool vIsSimilar = deltaV <= (float)MAX_DELTA_V/(float)DELTA_DENOMINATOR;

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