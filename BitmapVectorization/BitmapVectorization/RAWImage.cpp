#include "RawImage.h"

RawImage::RawImage( int a_width, int a_height )
{
	width = a_width;
	height = a_height;

	pPixelData = new Color*[ width * height ];

	for ( int index = 0; index < width * height; ++index )
	{
		pPixelData[ index ] = new Color();
	}
}

RawImage::~RawImage(void)
{
	for ( int i = 0; i < width * height; ++i )
	{
		delete pPixelData[i];
	}

	delete[] pPixelData;
}

Color** RawImage::getPixelData() const
{
	return pPixelData;
}

void RawImage::setPixel( int a_index, int a_r, int a_g, int a_b )
{
	if ( a_index < width * height )
	{
		pPixelData[ a_index ]->setRGB( a_r, a_g, a_b );
	}
}

int RawImage::getWidth() const
{
	return width;
}

int RawImage::getHeight() const
{
	return height;
}