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

	// Let's test whether the absolute value conversion is working
	nodeA.getColor().setYUV( 0, 0, 0 );
	nodeB.getColor().setYUV( Node::maxDeltaY() + 1 / 255,
							 Node::maxDeltaU() + 1 / 255,
							 Node::maxDeltaV() + 1 / 255 );

	// These nodes shouldn't be similar,
	// even though the original delta values are less than the maxes
	// (because they're negative)
	bool nodesNotSimilar = nodeA.isSimilar( nodeB );
	assert( nodesNotSimilar );
}

void testAddNode()
{
	// So we have two Nodes
	Node nodeA;
	Node nodeB;

	// Node A has 0 neighbors... for now
	int initialNeighborCount = nodeA.getNeighborCount();

	// Add a Node to Node A and see if the change in neighbors equals 1
	nodeA.addNode( &nodeB );
	bool addedNode = ( nodeA.getNeighborCount() - initialNeighborCount ) == 1;
	assert( addedNode );

	// Now add the Hot Spice 15(TM) to Node A
	// Total neighbors should not exceed 8 (max)
	for( int i = 0; i < 15; ++i )
	{
		nodeA.addNode( &Node() );
	}
	bool noMoreThanEight = nodeA.getNeighborCount() == 8;
	assert( noMoreThanEight );
}

void testRemoveNode()
{
	// Node babies = 2
	Node nodeA;
	Node nodeB;

	// Add Node B to Node A
	nodeA.addNode( &nodeB );
	int neighborCountAfterAdd = nodeA.getNeighborCount();

	// Remove Node B from Node A
	// Now Node A should have no nodes
	nodeA.removeNode( nodeB );
	bool noNeighborsThere = ( nodeA.getNeighborCount() - neighborCountAfterAdd ) == -1;
	assert( noNeighborsThere );

	// Now try removing Node B again (it's not Node A's neighbor)
	int neighborCountAfterRemoval = nodeA.getNeighborCount();
	nodeA.removeNode( nodeB );
	bool noEffectFromInvalidRemoval = ( nodeA.getNeighborCount() - neighborCountAfterRemoval ) == 0;
	assert( noEffectFromInvalidRemoval );
}

void runNodeTests()
{
	testIsSimilar();
	testAddNode();
	testRemoveNode();
	std::cout << "Node Tests Passed!" << std::endl;
}