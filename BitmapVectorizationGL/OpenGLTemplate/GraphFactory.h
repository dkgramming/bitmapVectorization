#pragma once

#include <iostream>

#include "Graph.h"
#include "ImageLoader.h"

using namespace std;

class GraphFactory
{
public:
	GraphFactory( char*, int, int );
	~GraphFactory(void);

	Graph* getGraph();

private:
	Graph* pGraph;
};

