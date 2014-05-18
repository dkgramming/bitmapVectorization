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
	bool isOnTop( int ) const;
	bool isOnBottom( int ) const;
	bool isOnLeft( int ) const;
	bool isOnRight( int ) const;
	const Coordinate getOffsetAt( NeighborDirection ) const;
	void markInvalidNeighbors( Node&, int, int );
};