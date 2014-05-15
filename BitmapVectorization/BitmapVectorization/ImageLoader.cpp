#include <fstream>
#include <iostream>
#include "ImageLoader.h"

using namespace std;

ImageLoader::ImageLoader(void)
{
}


ImageLoader::~ImageLoader(void)
{
}

bool ImageLoader::loadImage( char* a_path, Graph& a_graph )
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

		parseRawData( pFileContents, a_graph );

		delete[] pFileContents;

		return true;
	}

	return false;

}

void ImageLoader::parseRawData( char* a_pData, Graph& a_graph )
{
	int width = a_graph.getNumCols();
	int height = a_graph.getNumRows();

	const unsigned int TOTAL_COLOR_CHANNELS = width * height * 3;

	for( unsigned int index = 0; index < TOTAL_COLOR_CHANNELS; index += 3 )
	{
		// Arithmetic voodoo
		// @TODO: Figure out why this works
		int r = ( a_pData[ index ] + 256 ) % 256;
		int g = ( a_pData[ index + 1 ] + 256 ) % 256;
		int b = ( a_pData[ index + 2 ] + 256 ) % 256;

		a_graph.setColorAtNode( index / 3 , r, g, b );
	}
}

