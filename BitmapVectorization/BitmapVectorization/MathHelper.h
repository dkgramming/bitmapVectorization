#pragma once

#include <cmath>
#include <iostream>

using namespace std;

bool almostEquals( float lValue, float rValue )
{
	float difference = abs( lValue - rValue );
	float mean = ( lValue + rValue ) * 0.5f;
	float tolerance = ceil( mean * 0.01f ) / ( mean * mean );

	float TOLERANCE = 0.5f;

	return ( difference <= TOLERANCE );
}