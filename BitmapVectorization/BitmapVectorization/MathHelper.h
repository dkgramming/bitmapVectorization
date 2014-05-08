#pragma once

#include <cmath>
#include <iostream>

using namespace std;

bool almostEquals( float lValue, float rValue )
{
	float difference = abs( lValue - rValue );
	const float TOLERANCE = 0.1f;

	return ( difference <= TOLERANCE );
}