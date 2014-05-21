#include "VectorizedGraph.h"


VectorizedGraph::VectorizedGraph( char* a_path, int a_width, int a_height )
{
	graphFactory = new GraphFactory( a_path, a_width, a_height );
	graph = graphFactory->getGraph();
}


VectorizedGraph::~VectorizedGraph(void)
{
	delete graph;
	delete graphFactory;
}

int VectorizedGraph::getWidth() { return graph->getWidth(); }
int VectorizedGraph::getHeight() { return graph->getHeight(); }

Color VectorizedGraph::getColorAt( int x, int y )
{
	return graph->getNodeAt( x, y )->getColor();
}

Node* VectorizedGraph::getNodeAt( int x, int y )
{
	return graph->getNodeAt( x, y );
}