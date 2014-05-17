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
	runAllTests();

	// Dump that memory leak data
	_CrtDumpMemoryLeaks();
}
