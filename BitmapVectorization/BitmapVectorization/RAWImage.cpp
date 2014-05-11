#include "RawImage.h"

RawImage::RawImage( int a_width, int a_height )
{
	width = a_width;
	height = a_height;

	pixelData = new Color[ a_width * a_height ];
}


RawImage::~RawImage(void)
{
	delete[] pixelData;
}

Color* RawImage::getPixelData() const
{
	return pixelData;
}

void RawImage::setPixel( int x, int y, Color pixelColor )
{
	if ( x + ( y * width ) < width * height )
	{
		pixelData[ x + ( y * width ) ] = pixelColor;
	}
}