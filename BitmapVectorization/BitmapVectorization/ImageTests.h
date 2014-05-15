#pragma once

#include <cassert>

#include <iostream>

#include "ImageLoader.h"
#include "RawImage.h"
#include "Graph.h"

void testLoadImage()
{
	// Load raw image file
	ImageLoader loader;
	Graph graph( 4, 6 );

	bool imageLoaded = loader.loadImage( "Images/test1.raw", graph );

	assert( imageLoaded );
}

void runImageTests()
{
	testLoadImage();
	std::cout << "Image tests passed!" << std::endl;
}