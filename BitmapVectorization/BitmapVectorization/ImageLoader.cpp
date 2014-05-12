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

RawImage* ImageLoader::loadImage( char* a_path, int a_width, int a_height )
{
	ifstream fileIn( a_path, ios::binary );

	if ( fileIn.is_open() )
	{
		fileIn.seekg( 0, ios::end );
		int length = (int)fileIn.tellg();

		fileIn.seekg( 0, ios::beg );

		char* pFileContents = new char[ length + 1 ];
		fileIn.read( pFileContents, length );

		pFileContents[ length ] = 0;

		RawImage* pImage = parseRawData( pFileContents, a_width, a_height );
		return pImage;

		delete[] pFileContents;
	}

	RawImage* pDefaultImage = new RawImage( 0, 0 );

	return pDefaultImage;
}

RawImage* ImageLoader::parseRawData( char* data, int a_width, int a_height )
{
	RawImage* pImage = new RawImage( a_width, a_height );
	const unsigned int TOTAL_COLOR_CHANNELS = a_width * a_height * 3;

	for( int index = 0; index < TOTAL_COLOR_CHANNELS; index += 3 )
	{
		int r = ( data[ index ] + 256 ) % 256;
		int g = ( data[ index + 1 ] + 256 ) % 256;
		int b = ( data[ index + 2 ] + 256 ) % 256;

		cout << r << "\t" << g << "\t" << b << endl;
	}

	return pImage;
}

