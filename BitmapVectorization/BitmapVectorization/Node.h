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

private:
	vector<Node*> neighbors;
	Color color;
	int valence;

	static const unsigned int MAX_DELTA_Y = 48;
	static const unsigned int MAX_DELTA_U = 7;
	static const unsigned int MAX_DELTA_V = 6;
	static const unsigned int DELTA_DENOMINATOR = 255;

	static const int MAX_NODES = 8;
};

