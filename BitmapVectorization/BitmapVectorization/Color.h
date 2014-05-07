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

	unsigned int getR() const;
	unsigned int getG() const;
	unsigned int getB() const;
	
	void setY( float );
	void setU( float );
	void setV( float );
	void setYUV( float, float, float );

private:
	float y;
	float u;
	float v;

	static const unsigned int MAX_YUV_VALUE = 1;
	static const unsigned int MAX_RGB_VALUE = 255;
};

