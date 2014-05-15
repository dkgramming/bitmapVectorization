#pragma once

#include <cassert>

#include "ImageLoader.h"
#include "Graph.h"

void testGraphCreation()
{
	ImageLoader loader;
	const int COL_COUNT = 4;
	const int ROW_COUNT = 6;
	RawImage image( COL_COUNT, ROW_COUNT );
	loader.loadImage( "Images/test1.raw", COL_COUNT, ROW_COUNT, image );

	Graph graph( image );

	bool dimensionsMatch = ( graph.getNumRows() == ROW_COUNT ) && 
						   ( graph.getNumCols() == COL_COUNT );

	assert( dimensionsMatch );
}

void runGraphTests()
{
	testGraphCreation();
}