#include <fstream>
#include <iostream>
#include "ImageLoader.h"
#include "RawImage.h"

using namespace std;

ImageLoader::ImageLoader(void)
{
}


ImageLoader::~ImageLoader(void)
{
}

RawImage ImageLoader::loadImage( char* a_path, int a_width, int a_height )
{
	ifstream fileIn( a_path, ios::binary );

	if ( fileIn.is_open() )
	{
		fileIn.seekg( 0, ios::end );
		int length = (int)fileIn.tellg();

		fileIn.seekg( 0, ios::beg );

		char* fileContents = new char[ length + 1 ];
		fileIn.read( fileContents, length );

		fileContents[ length ] = 0;

		RawImage image = parseRawData( fileContents, a_width, a_height );
		return image;

		delete[] fileContents;
	}

	RawImage i( 0, 0 );
	return i;
}

RawImage ImageLoader::parseRawData( char* data, int a_width, int a_height )
{
	RawImage image( a_width, a_height );
	const unsigned int TOTAL_COLOR_CHANNELS = a_width * a_height * 3;

	for( int index = 0; index < TOTAL_COLOR_CHANNELS; index += 3 )
	{
		int r = ( data[ index ] + 256 ) % 256;
		int g = ( data[ index + 1 ] + 256 ) % 256;
		int b = ( data[ index + 2 ] + 256 ) % 256;

		cout << r << " " << g << " " << b << endl;
	}

	return image;
}

