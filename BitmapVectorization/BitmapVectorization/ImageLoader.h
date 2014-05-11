#pragma once

#include "RawImage.h"

class ImageLoader
{
public:
	ImageLoader(void);
	~ImageLoader(void);

	RawImage loadImage( char*, int, int );
	RawImage parseRawData( char*, int, int );
};

