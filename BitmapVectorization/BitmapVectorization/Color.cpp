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

float Color::getR() const
{
	float r = MAX_RGB_VALUE * ( y + v / 0.877f );
	r = ( r > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : r;
	return r;
}

float Color::getG() const
{
	float g = MAX_RGB_VALUE * ( y - 0.395f * u - 0.581f * v );
	g = ( g > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : g;
	return g;
}

float Color::getB() const
{
	float b = MAX_RGB_VALUE * ( y + u / 0.492f );
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

void Color::setYUV( int a_r, int a_g, int a_b )
{
	const float W_R = 0.299f;
	const float W_G = 0.587f;
	const float W_B = 0.114f;
	const float U_MAX = 0.436f;
	const float V_MAX = 0.615f;

	float y = ( W_R * a_r ) + ( W_G * a_g ) + ( W_B * a_b );
	float u = U_MAX * ( ( a_b - y ) / ( 1 - W_B ) );
	float v = V_MAX * ( ( a_r - y ) / ( 1 - W_R ) );

	setYUV( y, u, v );
}