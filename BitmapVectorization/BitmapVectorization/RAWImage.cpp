#include "RawImage.h"

RawImage::RawImage( int a_width, int a_height )
{
	width = a_width;
	height = a_height;

	pPixelData = new Color[ a_width * a_height ];
}

RawImage::~RawImage(void)
{
	delete[] pPixelData;
}

Color* RawImage::getPixelData() const
{
	return pPixelData;
}

void RawImage::setPixel( int a_x, int a_y, Color pixelColor )
{
	if ( a_x + ( a_y * width ) < width * height )
	{
		pPixelData[ a_x + ( a_y * width ) ] = pixelColor;
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