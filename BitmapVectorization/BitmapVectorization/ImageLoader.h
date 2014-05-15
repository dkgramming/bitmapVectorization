#pragma once

#include "RawImage.h"

class ImageLoader
{
public:
	ImageLoader(void);
	~ImageLoader(void);

	bool loadImage( char*, int, int, RawImage& );
	void parseRawData( char*, RawImage& );
};

