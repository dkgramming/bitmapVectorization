#pragma once

#include <GL\glew.h>

class Shape
{
public:
	Shape( GLfloat* vertices, int totalVertices, GLuint shaderProgramIndex );
	virtual ~Shape(void);

	virtual void draw( float x, float y, float xScale, float yScale, GLuint drawType = GL_TRIANGLE_FAN );

protected:
	GLuint vboIndex;
	GLuint vaoIndex;
	GLuint shaderProgramIndex;

	GLint offsetIndex;
	GLint scaleIndex;

	GLsizei totalVertices;
};

