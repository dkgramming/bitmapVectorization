#pragma once

class Color
{
public:
	Color(void);
	Color( float, float, float );
	Color( unsigned int, unsigned int, unsigned int );
	~Color(void);

	unsigned int getY() const;
	unsigned int getU() const;
	unsigned int getV() const;

	unsigned int getR() const;
	unsigned int getG() const;
	unsigned int getB() const;
	
	void setY( unsigned int );
	void setU( unsigned int );
	void setV( unsigned int );
	void setYUV( unsigned int, unsigned int, unsigned int );

private:
	float y;
	float u;
	float v;

	static const unsigned int MAX_YUV_VALUE = 1;
	static const unsigned int MAX_RGB_VALUE = 255;
};

