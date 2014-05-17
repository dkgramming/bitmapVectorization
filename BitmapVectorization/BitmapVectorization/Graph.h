#pragma once

#include "Node.h"
#include "RAWImage.h"

class Graph
{
public:
	Graph( int, int );
	~Graph(void);
	void setColorAtNode( int, int, int, int, int );
	void printRgbAtNode( int, int );

	int getNumRows() const;
	int getNumCols() const;

private:
	Node*** pNodes;
	int height;
	int width;
	
	void connectNodes();
	bool isOnTop( int );
	bool isOnBottom( int );
	bool isOnLeft( int );
	bool isOnRight( int );
	void markInvalidNeighbors( Node, int, int );
};