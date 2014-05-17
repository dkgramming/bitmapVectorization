#pragma once

class Color
{
public:
	Color( void );
	Color( float, float, float );
	~Color( void );

	float getY() const;
	float getU() const;
	float getV() const;

	int getR() const;
	int getG() const;
	int getB() const;
	
	void setYUV( float, float, float );
	void setRGB( int, int, int );

private:
	float y;
	float u;
	float v;

	int r;
	int g;
	int b;
	
	void setY( float );
	void setU( float );
	void setV( float );
	
	void setR( int );
	void setG( int );
	void setB( int );
	
	void updateRGB();
	void updateYUV();

	static const unsigned int MAX_YUV_VALUE = 1;
	static const unsigned int MAX_RGB_VALUE = 255;
};

