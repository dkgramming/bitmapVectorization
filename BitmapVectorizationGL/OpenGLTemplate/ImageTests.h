#pragma once

#include <cassert>

#include <iostream>

#include "ImageLoader.h"
#include "Graph.h"

void testLoadImage()
{
	// Load raw image file
	ImageLoader loader;
	Graph graph( 4, 4 );

	bool imageLoaded = loader.loadImage( "Images/test0.raw", graph );

	assert( imageLoaded );
}

void runImageTests()
{
	testLoadImage();
	std::cout << "Image tests passed!" << std::endl;
}