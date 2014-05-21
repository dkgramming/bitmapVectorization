#include "Coordinate.h"


Coordinate::Coordinate()
{
	Coordinate( 0, 0 );
}

Coordinate::Coordinate( int a_x, int a_y )
{
	setX( a_x );
	setY( a_y );
}


Coordinate::~Coordinate(void)
{
}

int Coordinate::getX() const { return x; }
int Coordinate::getY() const { return y; }

void Coordinate::setX( int a_x ) { x = a_x; }
void Coordinate::setY( int a_y ) { y = a_y; }

void Coordinate::print()
{
	cout << "{ " << getX() << ", " << getY() << " }";
}

bool Coordinate::operator==( const Coordinate& otherCoord )
{
	return ( x == otherCoord.getX() && y == otherCoord.getY() );
}

bool Coordinate::operator!=( const Coordinate& otherCoord )
{
	return !( x == otherCoord.getX() && y == otherCoord.getY() );
}