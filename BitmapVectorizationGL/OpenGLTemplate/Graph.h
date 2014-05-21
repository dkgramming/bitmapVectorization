#pragma once

#include "Node.h"

class Graph
{
public:
	Graph( int, int );
	~Graph(void);
	void setColorAtNode( int, int, int, int, int );
	void printRgbAtNode( int, int );

	int getHeight() const;
	int getWidth() const;

	Node* getNodeAt( int, int ) const;

	void severDissimilarNodes();
	void severDissimilarNeighbors( int, int );
	void resolveCrossedConnections();
	void resetCurve( Node*, Node* ) const;
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
	int getBranchLength( Node*, Node* ) const;
	const Coordinate getOffsetAt( NeighborDirection ) const;
	int traverseCurve( Node*, Node* ) const;
	int getIslandVote( Node*, Node*, Node*, Node* );
	int getSparsenessVote( Node*, Node* );
	int getCurveVote( Node*, Node*, Node*, Node* );
};