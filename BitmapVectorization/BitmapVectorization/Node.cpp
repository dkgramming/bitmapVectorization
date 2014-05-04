#include "Node.h"

Node::Node(void) {}

Node::~Node(void) {}

/**
 * TODO
 * Check if this node is similar to another
 */
bool Node::isSimilar( const Node& otherNode )
{
	return false;
}

/**
 * Add a node to this node
 */
void Node::addNode( Node* nodeToAdd )
{
	if ( neighbors.size() < MAX_NODES )
		neighbors.push_back( nodeToAdd );
}

/**
 * Remove a node from this node
 */
void Node::removeNode( const Node& nodeToRemove )
{
	// Search through all nodes 
	for ( int i = 0; i < neighbors.size(); ++i )
	{
		Node* n = neighbors[i];

		// If the node currently being checked has the
		// same memory address as the nodeToRemove,
		// remove it from our list of nodes.
		if ( n == &nodeToRemove )
		{
			neighbors.erase( neighbors.begin() + i );
			break;
		}
	}
}