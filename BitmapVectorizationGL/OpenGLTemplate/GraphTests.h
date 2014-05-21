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

	bool dimensionsMatch = ( graph.getHeight() == ROW_COUNT ) && 
						   ( graph.getWidth() == COL_COUNT );

	assert( dimensionsMatch );
}

void testResetCurve()
{
	ImageLoader loader;
	const int COL_COUNT = 4;
	const int ROW_COUNT = 4;
	Graph graph( COL_COUNT, ROW_COUNT );
	loader.loadImage( "Images/test0.raw", graph );

	for( int y = 0; y < ROW_COUNT; ++y )
	{
		for( int x = 0; x < COL_COUNT; ++x )
		{
			graph.getNodeAt( x, y )->setTraversal( true );
			bool traversed = 
				graph.getNodeAt( x, y )->getTraversed();

			assert( traversed );
		}
	}
}

void runGraphTests()
{
	testGraphCreation();
	testResetCurve();
	std::cout << "Graph tests passed!" << std::endl;
}