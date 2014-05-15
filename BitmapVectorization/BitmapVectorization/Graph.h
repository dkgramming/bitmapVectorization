#pragma once

#include "Node.h"
#include "RAWImage.h"

class Graph
{
public:
	Graph( RawImage );
	~Graph(void);
	void setNodeColors( const RawImage& );

private:
	Node** nodes;
	int numRows;
	int numColumns;
};