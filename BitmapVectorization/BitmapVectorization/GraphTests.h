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

	graph.resetCurve( (Node*)nullptr, (Node*)nullptr );

	for( int y = 0; y < ROW_COUNT; ++y )
	{
		for( int x = 0; x < COL_COUNT; ++x )
		{
			bool notTraversed = 
				!graph.getNodeAt( x, y )->getTraversed();

			assert( notTraversed );
		}
	}
}

void runGraphTests()
{
	testGraphCreation();
	testResetCurve();
	std::cout << "Graph tests passed!" << std::endl;
}