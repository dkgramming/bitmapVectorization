#include "Coordinate.h"


Coordinate::Coordinate()
{
	Coordinate( 0, 0 );
}

Coordinate::Coordinate( int a_x, int a_y )
{
	x = a_x;
	y = a_y;
}


Coordinate::~Coordinate(void)
{
}

int Coordinate::getX() const { return x; }
int Coordinate::getY() const { return y; }

void Coordinate::setX( int a_x ) { x = a_x; }
void Coordinate::setY( int a_y ) { y = a_y; }