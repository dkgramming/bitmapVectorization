#pragma once

#include <cassert>

#include "Color.h"
#include "MathHelper.h"

/**
 * Color unit tests
 */

void testGetR()
{
	// Test for 0
	Color color( 0.0f, 0.0f, 0.0f );
	bool isZero = color.getR() == 0;
	assert( isZero );

	// Test for 102
	color.setYUV( .369f, .229f, .027f );
	cout << color.getR() << endl;
	bool isOneOTwo = almostEquals( color.getR(), 102.0f );
	assert( isOneOTwo );

	// Test for 255
	color.setYUV( 1.0f, 0.0f, 0.0f );
	bool isTwoFiddyFie = color.getR() == 255;
	assert( isTwoFiddyFie );
}

void testGetG()
{
	// Test for 0
	Color color( 0.0f, 0.0f, 0.0f );
	bool isZero = color.getG() == 0;
	assert( isZero );

	// Test for 67
	color.setYUV( .369f, .229f, .027f );
	bool isSittySen = almostEquals( color.getG(), 67.0f );
	assert( isSittySen );

	// Test for 255
	color.setYUV( 1.0f, 0.0f, 0.0f );
	bool isTwoFiddyFie = color.getG() == 255;
	assert( isTwoFiddyFie );
}

void testGetB()
{
	// Test for 0
	Color color( 0.0f, 0.0f, 0.0f );
	bool isZero = ( color.getB() == 0 );
	assert( isZero );

	// Test for 213
	color.setYUV( .369f, .229f, .027f );
	bool isTooTirteen = almostEquals( color.getB(), 213.0f );
	assert( isTooTirteen );

	// Test for 255
	color.setYUV( 1.0f, 0.0f, 0.0f );
	bool isTwoFiddyFie = ( color.getB() == 255 );
	assert( isTwoFiddyFie );
}

void testSetYUV()
{
	float y = 0.0f;
	float u = 0.0f;
	float v = 0.0f;
	Color testColor( y, u, v );

	int r = 0;
	int g = 0;
	int b = 0;
	testColor.setYUV( r, g, b );

	bool yIsZero = ( testColor.getY() == 0.0f );
	bool uIsZero = ( testColor.getU() == 0.0f );
	bool vIsZero = ( testColor.getV() == 0.0f );

	assert( yIsZero && uIsZero && vIsZero );
}

void runColorTests()
{
	testGetR();
	testGetG();
	testGetB();
	testSetYUV();
	std::cout << "Color tests passed!" << std::endl;
}