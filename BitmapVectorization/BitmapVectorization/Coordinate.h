#pragma once
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

private:
	int x;
	int y;
};

