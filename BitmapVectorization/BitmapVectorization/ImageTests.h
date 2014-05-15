#pragma once

#include <cassert>

#include <iostream>

#include "ImageLoader.h"

void testLoadImage()
{
	// Load raw image file
	ImageLoader loader;
	RawImage image( 0, 0 );

	bool imageLoaded = loader.loadImage( "Images/test1.raw", 4, 6, image );

	assert( imageLoaded );
}

void runImageTests()
{
	testLoadImage();

	std::cout << "Image tests passed!" << std::endl;
}