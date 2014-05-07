#pragma once

#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

bool almostEquals( float lValue, float rValue, int decimalPointPrecision )
{
	return abs( lValue - rValue ) <= numeric_limits<float>::epsilon() *
									 max( abs( lValue ), abs( rValue ) ) *
									 decimalPointPrecision;
}