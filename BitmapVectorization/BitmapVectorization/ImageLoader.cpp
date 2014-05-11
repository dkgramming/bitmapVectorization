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

RawImage ImageLoader::loadImage( char* path, int width, int height )
{
	ifstream fileIn( path, ios::binary );

	if ( fileIn.is_open() )
	{
		fileIn.seekg( 0, ios::end );
		int length = (int)fileIn.tellg();

		fileIn.seekg( 0, ios::beg );

		char* fileContents = new char[ length + 1 ];
		fileIn.read( fileContents, length );

		fileContents[ length ] = 0;

		RawImage image = parseRawData( fileContents, width, height );
		return image;

		delete[] fileContents;
	}

	RawImage i( 0, 0 );
	return i;
}

RawImage ImageLoader::parseRawData( char* data, int width, int height )
{
	RawImage image( width, height );
	
	for( int i = 0; i < width * height * 3; i += 3 )
	{
		int r = ( data[ i ] + 256 ) % 256;
		int g = ( data[ i + 1 ] + 256 ) % 256;
		int b = ( data[ i + 2 ] + 256 ) % 256;

		cout << r << " " << g << " " << b << endl;
	}

	return image;
}

