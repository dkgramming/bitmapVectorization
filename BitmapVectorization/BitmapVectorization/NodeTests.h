#pragma once

#include <cassert>
#include <iostream>

#include "Node.h"

/**
 * Node unit tests
 */

void testIsSimilar()
{
	// Let's start with two identical nodes
	Node nodeA;
	Node nodeB( nodeA ); // Create using copy constructor

	// Check if the two nodes are similar
	bool nodesAreSimilar = nodeA.isSimilar( nodeB );
	assert( nodesAreSimilar );

	// Let's make these nodes a little spicier
	nodeA.getColor().setYUV( 0, 0, 0 );
	nodeB.getColor().setYUV( .5f, .5f, .5f );

	// Check if the two nodes are similar
	// They shouldn't be
	bool nodesAintSimilar = nodeA.isSimilar( nodeB );
	assert( nodesAintSimilar );

	// Now let's verify the similarity tolerance thresholds
	nodeA.getColor().setYUV( 0, 0, 0 );
	nodeB.getColor().setYUV( Node::maxDeltaY(), 
							 Node::maxDeltaU(), 
							 Node::maxDeltaV() );

	// Check if the two nodes are similar
	bool nodesAtThresholdSimilar = nodeA.isSimilar( nodeB );
	assert( nodesAtThresholdSimilar );
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