// These are for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "Node.h"
#include "Graph.h"
#include "UnitTests.h"
#include "ImageLoader.h"

void runProgram()
{
	ImageLoader loader;
	Graph graph( 4, 4 );

	loader.loadImage( "Images/test2.raw", graph );

	graph.print();
	graph.severDissimilarNodes();
	graph.print();
	graph.resolveCrossedConnections();
	graph.print();
}

int main()
{
	runAllTests();

	runProgram();

	// Dump that memory leak data
	_CrtDumpMemoryLeaks();
}
