#pragma once

#include <cassert>

#include <iostream>

#include "ImageLoader.h"
#include "RawImage.h"

void testLoadImage()
{
	// Load raw image file
	ImageLoader loader;
	RawImage image( 0, 0 );

	bool imageLoaded = loader.loadImage( "Images/test1.raw", 4, 6, image );

	assert( imageLoaded );
}

void testSetPixel()
{
	RawImage image( 4, 6 );
	ImageLoader loader;
	loader.loadImage( "Images/test1.raw", 4, 6, image );

	// Loop through the pixel data to ensure that it's been modified
	Color** testPixelData = image.getPixelData();

	auto pixelCount = ( image.getWidth() * image.getHeight() );
	for( auto index = 0; index < pixelCount; ++index )
	{
		auto y = testPixelData[ index ]->getY();
		auto u = testPixelData[ index ]->getU();
		auto v = testPixelData[ index ]->getV();

		bool notAllZero = !( y == 0.0f && u == 0.0f && v == 0.0f );

		assert( notAllZero );
	} 
}

void runImageTests()
{
	testLoadImage();
	testSetPixel();
	std::cout << "Image tests passed!" << std::endl;
}