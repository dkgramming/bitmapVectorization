#pragma once

#include <cassert>

#include <iostream>

#include "ImageLoader.h"
#include "Graph.h"

void testGraphCreation()
{
	ImageLoader loader;
	const int COL_COUNT = 4;
	const int ROW_COUNT = 4;
	Graph graph( COL_COUNT, ROW_COUNT );
	loader.loadImage( "Images/test0.raw", graph );

	bool dimensionsMatch = ( graph.getNumRows() == ROW_COUNT ) && 
						   ( graph.getNumCols() == COL_COUNT );

	assert( dimensionsMatch );
}

void testNodeColors()
{
	ImageLoader loader;
	const int COL_COUNT = 4;
	const int ROW_COUNT = 4;
	Graph graph( COL_COUNT, ROW_COUNT );
	loader.loadImage( "Images/test0.raw", graph );

	for( int index = 0; index < COL_COUNT * ROW_COUNT; ++index )
	{
		graph.printRgbAtNode( index );
	}
}

void runGraphTests()
{
	testGraphCreation();
	testNodeColors();
	std::cout << "Graph tests passed!" << std::endl;
}