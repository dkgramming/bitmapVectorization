#include <cmath>

#include "Color.h"

Color::Color( void )
{
	Color( 0.0f, 0.0f, 0.0f );
}

Color::Color( float a_y, float a_u, float a_v )
{
	setYUV( a_y, a_u, a_v );
}

Color::~Color(void)
{
	// Do nothing
}

float Color::getY() const { return y; }

float Color::getU() const { return u; }

float Color::getV() const { return v; }

unsigned int Color::getR() const
{
	unsigned int r = (unsigned int)ceilf( MAX_RGB_VALUE * ( y + v / 0.877f ) );
	r = ( r > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : r;
	return r;
}

unsigned int Color::getG() const
{
	unsigned int g = (unsigned int)ceilf( MAX_RGB_VALUE * ( y - 0.395f * u - 0.581f * v ) );
	g = ( g > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : g;
	return g;
}

unsigned int Color::getB() const
{
	unsigned int b = (unsigned int)ceilf( MAX_RGB_VALUE * ( y + u / 0.492f ) );
	b = ( b > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : b;
	return b;

}

void Color::setY( float a_y )
{
	y = ( a_y > MAX_YUV_VALUE ) ? MAX_YUV_VALUE : a_y;
}

void Color::setU( float a_u )
{
	u = ( a_u > MAX_YUV_VALUE ) ? MAX_YUV_VALUE : a_u;
}

void Color::setV( float a_v )
{
	v = ( a_v > MAX_YUV_VALUE ) ? MAX_YUV_VALUE : a_v;
}

void Color::setYUV( float a_y, float a_u, float a_v )
{
	setY( a_y );
	setU( a_u );
	setV( a_v );
}