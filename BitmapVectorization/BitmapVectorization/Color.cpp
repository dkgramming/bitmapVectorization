#include "Color.h"

Color::Color( void )
{
	Color( 0.0f, 0.0f, 0.0f );
}

Color::Color( float a_y, float a_u, float a_v )
{
	setYUV( a_y, a_u, a_v );
}

Color::Color( unsigned int a_y, unsigned int a_u, unsigned int a_v )
{
	setYUV( a_y, a_u, a_v );
}

Color::~Color(void)
{
	// Do nothing
}

unsigned int Color::getY() const { return y; }

unsigned int Color::getU() const { return u; }

unsigned int Color::getV() const { return v; }

unsigned int Color::getR() const
{
	unsigned int r = y + (unsigned int)( 1.772f * v );
	r = ( r > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : r;
	return r;
}

unsigned int Color::getG() const
{
	unsigned int g = y - (unsigned int)( 0.344f * v + 0.714f * u );
	g = ( g > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : g;
	return g;
}

unsigned int Color::getB() const
{
	unsigned int b = y + (unsigned int)( 1.402f * u );
	b = ( b > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : b;
	return b;
}

void Color::setY( unsigned int a_y )
{
	y = ( a_y > MAX_YUV_VALUE ) ? MAX_YUV_VALUE : a_y;
}

void Color::setU( unsigned int a_u )
{
	u = ( a_u > MAX_YUV_VALUE ) ? MAX_YUV_VALUE : a_u;
}

void Color::setV( unsigned int a_v )
{
	v = ( a_v > MAX_YUV_VALUE ) ? MAX_YUV_VALUE : a_v;
}

void Color::setYUV( unsigned int a_y, unsigned int a_u, unsigned int a_v )
{
	setY( a_y );
	setU( a_u );
	setV( a_v );
}