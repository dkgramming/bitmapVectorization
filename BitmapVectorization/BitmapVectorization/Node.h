#pragma once

#include <vector>

#include "Color.h"

using namespace std;

class Node
{
public:
	Node( void );
	~Node( void );

	bool isSimilar( const Node& );
	void addNode( Node* );
	void removeNode( const Node& );
	static const float maxDeltaY();
	static const float maxDeltaU();
	static const float maxDeltaV();
	Color getColor() const;

private:
	vector<Node*> neighbors;
	Color color;
	int valence;

	static const int MAX_NODES = 8;
};

