#pragma once

#include "GraphFactory.h"
#include "Color.h"

class VectorizedGraph
{
public:
	VectorizedGraph( char*, int, int );
	~VectorizedGraph(void);

	void draw();
	int getWidth();
	int getHeight();
	Color getColorAt( int, int );
	Node* getNodeAt( int, int );

private:
	GraphFactory* graphFactory;
	Graph* graph;
};

