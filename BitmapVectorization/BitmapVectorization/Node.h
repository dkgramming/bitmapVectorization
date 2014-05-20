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
	static const int DEFAULT = -2;
	static const int SEVERED = -3;

	Node( int x = DEFAULT, int y = DEFAULT );
	~Node( void );

	bool isSimilar( const Node* ) const;
	void severConnection( NeighborDirection );
	bool isSevered( NeighborDirection ) const;
	bool neighborExistsAt( NeighborDirection ) const;
	Coordinate getNextNeighbor( int );
	static const float maxDeltaY();
	static const float maxDeltaU();
	static const float maxDeltaV();
	
	Coordinate getNeighborCoord( NeighborDirection );
	void setNeighbor( int, int, NeighborDirection );
	int getNeighborCount() const;
	Color getColor() const;
	void setColor( Color );

	int getX();
	int getY();

	bool getTraversed();
	void setTraversal( bool );

	void printRgb() const;

	void print();

private:
	Coordinate **neighbors;
	Color color;
	int x;
	int y;
	int neighborCount;
	bool traversed;
};