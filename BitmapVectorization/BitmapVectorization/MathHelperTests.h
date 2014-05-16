#pragma once

#include <cassert>

#include "MathHelper.h"

void testAlmostEquals()
{
	// Test really close number round-off errors
    float f1 = 0.2f;
    float f2 = (float)( 1 / std::sqrt( 5 ) / std::sqrt( 5 ) );
	assert( almostEquals( f1, f2 ) );

	// Test one decimal point off
	f1 = 0.1f;
	f2 = 0.2f;
	assert( almostEquals( f1, f2 ) );

	// Test near-zero values
	f1 = 0.0f;
	f2 = 0.00001f;
	assert( almostEquals( f1, f2 ) );

	// Test far-away numbs
	f1 = 0.0f;
	f2 = 2.0f;
	assert( !almostEquals( f1, f2 ) );

	// Test real far numbies
	f1 = 1000.0f;
	f2 = 999.0f;
	assert( almostEquals( f1, f2 ) );
}

void runMathHelperTests()
{
	testAlmostEquals();
	std::cout << "Math helper tests passed!" << std::endl;
}