#pragma once

#include "Node.h"
#include "RAWImage.h"

class Graph
{
public:
	Graph( int, int );
	~Graph(void);
	void setColorAtNode( int, int, int, int );
	void printRgbAtNode( int );

	int getNumRows() const;
	int getNumCols() const;

private:
	Node** pNodes;
	int numRows;
	int numColumns;
};