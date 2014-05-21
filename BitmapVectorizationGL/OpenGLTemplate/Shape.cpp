#include "Shape.h"
#include "ShaderHelpers.h"
#include <iostream>

using namespace std;

Shape::Shape( GLfloat* vertices, int totalVertices, GLuint shaderProgramIndex )
{
	this->shaderProgramIndex = shaderProgramIndex;
	this->totalVertices = totalVertices;

	glGenVertexArrays( 1, &vaoIndex );

	// Set newly created VAO as the active one
	glBindVertexArray( vaoIndex );

	glGenBuffers( 1, &vboIndex );

	// Set newly created VBO as the active one
	glBindBuffer( GL_ARRAY_BUFFER, vboIndex );

	// Copy vertex data into OpenGL buffer
	glBufferData( GL_ARRAY_BUFFER, 2 * sizeof( float ) * totalVertices, vertices, GL_STATIC_DRAW );

	// Describe layout of data to OpenGL
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glEnableVertexAttribArray( 0 );

	// Get locations of uniform variables in the shader program
	offsetIndex = glGetUniformLocation( shaderProgramIndex, "offset" );
	scaleIndex = glGetUniformLocation( shaderProgramIndex, "scale" );
}


Shape::~Shape(void)
{
	glDeleteVertexArrays( 1, &vaoIndex );
	glDeleteBuffers( 1, &vboIndex );
}


// Draw the shape to the screen
void Shape::draw( float x, float y, float xScale, float yScale, GLuint drawType )
{
	glProgramUniform2f( shaderProgramIndex, offsetIndex, x, y );
	glProgramUniform2f( shaderProgramIndex, scaleIndex, xScale, yScale );

	// Bind VAO
	glBindVertexArray( vaoIndex );

	// Have OpenGL draw using the currently bound buffer
	glDrawArrays( drawType, 0, totalVertices );
}
