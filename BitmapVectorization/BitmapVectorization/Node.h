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
	Node( void );
	~Node( void );

	bool isSimilar( const Node& );
	void severConnection( NeighborDirection );
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
	static const int MAX_NODES = 8;

	Coordinate *neighbors[ MAX_NODES ];
	Color color;
	int valence;
};