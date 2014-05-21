#pragma once

#include "Shape.h"

class Line :
	public Shape
{
public:
	Line( GLfloat* vertices, GLuint shaderProgramIndex );
	~Line(void);

	void draw( float x, float y, float xScale, float yScale, GLuint drawType = GL_LINE_STRIP );
};

