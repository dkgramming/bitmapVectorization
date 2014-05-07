#pragma once

#include <cassert>

#include "Color.h"

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
	bool isOneOTwo = color.getR() == 102;
	assert( isOneOTwo );

	// Test for 255
	color.setYUV( 1.0f, 0.0f, 0.0f );
	bool isTwoFiddyFie = color.getR() == 255;
	std::cout << "R = " << color.getR() << std::endl;
	assert( isTwoFiddyFie );
}

void runColorTests()
{
	testGetR();
	std::cout << "Color tests Passed!" << std::endl;
}