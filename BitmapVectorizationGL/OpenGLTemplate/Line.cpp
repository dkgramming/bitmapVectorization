#include "Line.h"
#include <iostream>

using namespace std;

Line::Line( GLfloat* vertices, GLuint shaderProgramIndex )
	:Shape( vertices, 4, shaderProgramIndex )
{
}


Line::~Line(void)
{
}


// Draw the shape to the screen
void Line::draw( float x, float y, float xScale, float yScale, GLuint drawType )
{
	glProgramUniform2f( shaderProgramIndex, offsetIndex, x, y );
	glProgramUniform2f( shaderProgramIndex, scaleIndex, xScale, yScale );

	// Bind VAO
	glBindVertexArray( vaoIndex );

	// Have OpenGL draw using the currently bound buffer
	glDrawArrays( drawType, 0, totalVertices );
}
