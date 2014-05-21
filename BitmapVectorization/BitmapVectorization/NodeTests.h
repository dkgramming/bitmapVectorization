#pragma once

#include <cassert>
#include <iostream>

#include "Node.h"

/**
 * Node unit tests
 */

void testGetNeighborCount()
{
	Node nodeA;

	int currentNeighborCount = nodeA.getNeighborCount();
	bool noNeighborsYet = ( currentNeighborCount == 0 );
	assert( noNeighborsYet );

	nodeA.setNeighbor( 0, 0, NeighborDirection::LEFT );
	currentNeighborCount = nodeA.getNeighborCount();
	bool neighborAdded = ( currentNeighborCount == 1 );
	assert( neighborAdded );

	for( int i = 0; i < 8; ++i )
	{
		nodeA.setNeighbor( 0, 0, NeighborDirection( i ) );
	}
	bool neighborsFilled = ( nodeA.getNeighborCount() == 8 );
	assert( neighborsFilled );

	nodeA.severConnection( NeighborDirection::LEFT );
	bool neighborRemoved = ( nodeA.getNeighborCount() == 7 );
	assert( neighborRemoved );
}

void testIsSimilar()
{
	// Let's start with two identical nodes
	Node nodeA;
	Node nodeB; // Create using copy constructor

	// Check if the two nodes are similar
	bool nodesAreSimilar = nodeA.isSimilar( &nodeB );
	assert( nodesAreSimilar );

	// Let's make these nodes a little spicier
	nodeA.getColor().setYUV( 0, 0, 0 );
	nodeB.getColor().setYUV( .5f, .5f, .5f );

	// Check if the two nodes are similar
	// They shouldn't be
	bool nodesAintSimilar = nodeA.isSimilar( &nodeB );
	assert( nodesAintSimilar );

	// Now let's verify the similarity tolerance thresholds
	nodeA.getColor().setYUV( 0, 0, 0 );
	nodeB.getColor().setYUV( Node::maxDeltaY(), 
							 Node::maxDeltaU(), 
							 Node::maxDeltaV() );

	// Check if the two nodes are similar
	bool nodesAtThresholdSimilar = nodeA.isSimilar( &nodeB );
	assert( nodesAtThresholdSimilar );

	// Let's test whether the absolute value conversion is working
	nodeA.getColor().setYUV( 0, 0, 0 );
	nodeB.getColor().setYUV( Node::maxDeltaY() + 1 / 255,
							 Node::maxDeltaU() + 1 / 255,
							 Node::maxDeltaV() + 1 / 255 );

	// These nodes shouldn't be similar,
	// even though the original delta values are less than the maxes
	// (because they're negative)
	bool nodesNotSimilar = nodeA.isSimilar( &nodeB );
	assert( nodesNotSimilar );
}

void testSeverConnection()
{
	Node nodeA;

	for( int i = 0; i < 8; ++i )
	{
		nodeA.setNeighbor( 0, 0, NeighborDirection( i ) );
	}

	nodeA.severConnection( NeighborDirection::LEFT );
	bool neighborRemoved = ( nodeA.getNeighborCount() == 7 );
	assert( neighborRemoved );

	// Try to remove the same neighbor twice in a row
	nodeA.severConnection( NeighborDirection::LEFT );
	bool noNewNeighborRemoved = ( nodeA.getNeighborCount() == 7 );
	assert( noNewNeighborRemoved );

	for( int i = 0; i < 8; ++i )
	{
		nodeA.severConnection( NeighborDirection( i ) );
	}
	bool allNeighborsDead = ( nodeA.getNeighborCount() == 0 );
	assert( allNeighborsDead );
}

void runNodeTests()
{
	testGetNeighborCount();
	testIsSimilar();
	testSeverConnection();
	std::cout << "Node tests passed!" << std::endl;
}