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

void Color::updateRGB()
{
	r = (int)( MAX_RGB_VALUE * ( y + v / 0.877f ) );
	r = ( r > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : r;

	g = (int)( MAX_RGB_VALUE * ( y - 0.395f * u - 0.581f * v ) );
	g = ( g > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : g;
	
	b = (int)( MAX_RGB_VALUE * ( y + u / 0.492f ) );
	b = ( b > MAX_RGB_VALUE ) ? MAX_RGB_VALUE : b;
}

void Color::updateYUV()
{
	const float W_R = 0.299f;
	const float W_G = 0.587f;
	const float W_B = 0.114f;
	const float U_MAX = 0.436f;
	const float V_MAX = 0.615f;

	y = ( W_R * r ) + ( W_G * g ) + ( W_B * b );
	u = U_MAX * ( ( b - y ) / ( 1 - W_B ) );
	v = V_MAX * ( ( r - y ) / ( 1 - W_R ) );
}

float Color::getY() const { return y; }

float Color::getU() const { return u; }

float Color::getV() const { return v; }

int Color::getR() const { return r; }
						  
int Color::getG() const { return g; }
						  
int Color::getB() const { return b; }

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

void Color::setR( int a_r )
{
	r = a_r;
}

void Color::setG( int a_g )
{
	g = a_g;
}

void Color::setB( int a_b )
{
	b = a_b;
}

void Color::setYUV( float a_y, float a_u, float a_v )
{
	setY( a_y );
	setU( a_u );
	setV( a_v );
	updateRGB();
}

void Color::setRGB( int a_r, int a_g, int a_b )
{
	setR( a_r );
	setG( a_g );
	setB( a_b );
	updateYUV();
}

float Color::getOpenGL_R() const { return r / 255.0f; }
float Color::getOpenGL_G() const { return g / 255.0f; }
float Color::getOpenGL_B() const { return b / 255.0f; }