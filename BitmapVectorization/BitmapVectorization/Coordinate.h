#pragma once

#include <iostream>
#include "Coordinate.h"

using namespace std;

class Coordinate
{
public:
	Coordinate(void);
	Coordinate( int, int );
	~Coordinate(void);

	int getX() const;
	int getY() const;
	void setX( int );
	void setY( int );

	void print();

private:
	int x;
	int y;
};