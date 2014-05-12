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
	RawImage* pImage = new RawImage( 0, 0 );

	ifstream fileIn( a_path, ios::binary );

	if ( fileIn.is_open() )
	{
		fileIn.seekg( 0, ios::end );
		int length = (int)fileIn.tellg();

		fileIn.seekg( 0, ios::beg );

		char* pFileContents = new char[ length + 1 ];
		fileIn.read( pFileContents, length );

		pFileContents[ length ] = 0;

		// Must delete default image before reassigning 
		delete pImage;
		pImage = parseRawData( pFileContents, a_width, a_height );

		delete[] pFileContents;
	}

	return pImage;
}

RawImage* ImageLoader::parseRawData( char* a_pData, int a_width, int a_height )
{
	RawImage* pImage = new RawImage( a_width, a_height );
	const unsigned int TOTAL_COLOR_CHANNELS = a_width * a_height * 3;

	for( int index = 0; index < TOTAL_COLOR_CHANNELS; index += 3 )
	{
		// Arithmetic voodoo
		// @TODO: Figure out why this works
		int r = ( a_pData[ index ] + 256 ) % 256;
		int g = ( a_pData[ index + 1 ] + 256 ) % 256;
		int b = ( a_pData[ index + 2 ] + 256 ) % 256;
	}

	return pImage;
}

