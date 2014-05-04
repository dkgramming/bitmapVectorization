#include "Node.h"
#include <iostream>


Node::Node(void) {}

Node::~Node(void) {}

bool Node::isSimilar( const Node& otherNode )
{
	return false;
}

void Node::addNode( const Node& nodeToAdd )
{
	if ( neighbors.size() < MAX_NODES )
	{
		neighbors.push_back( nodeToAdd );
		cout << "NODE ADDED" << endl;
	}
}

void Node::removeNode( const Node& nodeToRemove )
{
	/*
	vector<Node>::iterator iterator;
	iterator = find( 
		neighbors.begin(), 
		neighbors.end(),
		nodeToRemove
		);
	
	if ( iterator != neighbors.end() )
	{
		neighbors.erase( iterator );
		cout << "NODE REMOVED" << endl;
	}
	*/
}