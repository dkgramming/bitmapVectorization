#pragma once

#include <vector>

#include "Color.h"
#include "Coordinate.h"

using namespace std;

enum NeighborDirection
{
	TOP_LEFT,
	TOP,
	TOP_RIGHT,
	LEFT,
	RIGHT,
	BOTTOM_LEFT,
	BOTTOM,
	BOTTOM_RIGHT
};

class Node
{
public:
	static const int MAX_NEIGHBORS = 8;

	Node( void );
	~Node( void );

	bool isSimilar( const Node& ) const;
	void severConnection( NeighborDirection );
	void invalidate( NeighborDirection );
	bool isValid( NeighborDirection ) const;
	bool neighborExistsAt( NeighborDirection ) const;
	static const float maxDeltaY();
	static const float maxDeltaU();
	static const float maxDeltaV();
	
	Coordinate getNeighborCoord( NeighborDirection );
	void setNeighbor( int, int, NeighborDirection );
	int getNeighborCount() const;
	Color getColor() const;
	void setColor( Color );

	void printRgb() const;

private:
	static const int INVALID = -2;

	Coordinate **neighbors;
	Color color;
	int valence;
};