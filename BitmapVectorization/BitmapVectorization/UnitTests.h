/**
 * Use this file to write unit tests
 * @TODO: Add tests for all components
 */

#pragma once

#include "NodeTests.h"
#include "ColorTests.h"
#include "MathHelperTests.h"

void runAllTests()
{
	runMathHelperTests();
	runColorTests();
	runNodeTests();
}