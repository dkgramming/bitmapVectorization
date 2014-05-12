#pragma once

#include "Color.h"

class RawImage
{
public:
	RawImage( int, int );
	~RawImage(void);

	Color* getPixelData() const;
	void setPixel( int, int, Color );

private:
	Color* pPixelData;
	int width;
	int height;
};
