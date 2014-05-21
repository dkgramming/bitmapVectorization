#include "GraphFactory.h"


GraphFactory::GraphFactory( char* a_path, int a_width, int a_height )
{
	pGraph = new Graph( a_width, a_height );

	ImageLoader imageLoader;
	imageLoader.loadImage( a_path, *pGraph );
	
	//pGraph->print();
	pGraph->severDissimilarNodes();
	//pGraph->print();
	pGraph->resolveCrossedConnections();
	//pGraph->print();
}


GraphFactory::~GraphFactory(void)
{
	delete pGraph;
}

Graph* GraphFactory::getGraph()
{
	return pGraph;
}
