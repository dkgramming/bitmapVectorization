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
	const float maxDeltaY() const;
	const float maxDeltaU() const;
	const float maxDeltaV() const;

private:
	vector<Node*> neighbors;
	Color color;
	int valence;

	static const int MAX_NODES = 8;
};

