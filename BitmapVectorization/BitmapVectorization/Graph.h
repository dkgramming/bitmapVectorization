#pragma once

#include "Node.h"
#include "RAWImage.h"

class Graph
{
public:
	Graph( RawImage );
	~Graph(void);
	void setNodeColors( const RawImage& );

	int getNumRows() const;
	int getNumCols() const;

private:
	Node** pNodes;
	int numRows;
	int numColumns;
};