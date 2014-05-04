#pragma once

#include "Node.h"

class Graph
{
public:
	Graph( int numRows, int numColumns );
	~Graph(void);

private:
	Node** nodes;
	int numRows;
	int numColumns;
};