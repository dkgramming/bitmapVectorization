// These are for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "Node.h"
#include "Graph.h"
#include "UnitTests.h"
#include "ImageLoader.h"

int main()
{
	// The main should be used for unit tests
	runAllTests();

	ImageLoader loader;
	RawImage* pImage = loader.loadImage( "Images/test1.raw", 4, 6 );
	delete pImage;

	// Dump that memory leak data
	_CrtDumpMemoryLeaks();
}