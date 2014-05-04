#pragma once

#include "Color.h"
#include <vector>

using namespace std;

class Node
{
public:
	Node( void );
	~Node( void );

	bool isSimilar( const Node& );
	void addNode( Node* );
	void removeNode( const Node& );

private:
	vector<Node*> neighbors;
	Color color;
	int valence;

	static const int MAX_NODES = 8;
};

