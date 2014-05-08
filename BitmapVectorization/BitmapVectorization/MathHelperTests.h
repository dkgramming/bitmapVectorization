#pragma once

#include <cassert>

#include "MathHelper.h"

void testAlmostEquals()
{
	// Test really close number round-off errors
    float d1 = 0.2f;
    float d2 = (float)( 1 / std::sqrt( 5 ) / std::sqrt( 5 ) );
	assert( almostEquals( d1, d2 ) );

	// Test one decimal point off
	float f1 = 0.1f;
	float f2 = 0.2f;
	assert( almostEquals( f1, f2 ) );
}

void runMathHelperTests()
{
	testAlmostEquals();
	std::cout << "Math Helper tests Passed!" << std::endl;
}