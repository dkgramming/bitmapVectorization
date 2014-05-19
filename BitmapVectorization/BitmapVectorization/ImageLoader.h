#pragma once

#include "Graph.h"

class ImageLoader
{
public:
	ImageLoader(void);
	~ImageLoader(void);

	bool loadImage( char*, Graph& );
	void parseRawData( char*, Graph& );
};

