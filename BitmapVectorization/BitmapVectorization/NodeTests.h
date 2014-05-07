#pragma once

#include <cassert>
#include <iostream>

#include "Node.h"

/**
 * Node unit tests
 */

void testIsSimilar()
{
	Node nodeA;
	Node nodeB( nodeA ); // Create using copy constructor

	// Check if the two nodes are similar
	bool nodesAreSimilar = nodeA.isSimilar( nodeB );
	assert( nodesAreSimilar );
}

void testAddNode()
{
	//@TODO: Write test
	//assert( false );
}

void testRemoveNode()
{
	//@TODO: Write test
	//assert( false );
}

void runNodeTests()
{
	testIsSimilar();
	testAddNode();
	testRemoveNode();
	std::cout << "Node Tests Passed!" << std::endl;
}