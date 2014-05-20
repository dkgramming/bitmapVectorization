#pragma once

#include "Node.h"

class Graph
{
public:
	Graph( int, int );
	~Graph(void);
	void setColorAtNode( int, int, int, int, int );
	void printRgbAtNode( int, int );

	int getNumRows() const;
	int getNumCols() const;

	void severDissimilarNodes();
	void resolveCrossedConnections();
	void print() const;

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
	int traverseCurve( Node*, Node* ) const;
	void resetCurve( Node*, Node* ) const;
};