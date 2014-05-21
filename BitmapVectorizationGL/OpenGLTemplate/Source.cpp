// Reuben Brenner-Adams
// David Kisluk
// Hector Pineiro II

// DSAI
// Final Project - Honors Contract Course
// Bitmap Vectorization

#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include "ShaderHelpers.h"
#include "Line.h"
#include "Shape.h"
#include "UnitTests.h"
#include "VectorizedGraph.h"

using namespace std;
using namespace glm;

enum ViewState
{
	ORIGINAL,
	VECTOR,
	PLANAR,
	LENGTH
};

/**
 * Global variables
 */
const float WIDTH = 900.0f;
const float HEIGHT = 600.0f;
const float ASPECT_RATIO = WIDTH / (float)HEIGHT;
const int CIRCLE_VERTICES = 30;
const float PI = 3.14159265358979f;

GLint programIndex;

vector<VectorizedGraph*> vectorizedGraphs;
ViewState viewState = ViewState::ORIGINAL;

/**
 * Shapes
 */
Shape* triangle;
Shape* rectangle;
Shape* circle;
Shape* semicircle;
Line* lineUpLeft;
Line* lineUp;
Line* lineUpRight;
Line* lineLeft;
Line* lineRight;
Line* lineDownLeft;
Line* lineDown;
Line* lineDownRight;


/**
 * Method declaration
 */
void init();
void update();
void draw();
void drawShape( Shape*, float, float, float, float );
void drawOriginalImage( VectorizedGraph*, float, float, float, float );
void drawVectorizedGraph( VectorizedGraph*, float, float, float, float );
void drawPlanarGraph( VectorizedGraph*, float, float, float, float );
void adjustVerticesPosition( GLfloat*, int, bool = true );
void onKeyPress( unsigned char, int, int );

int main( int argc, char** argv )
{
	glewExperimental = GL_TRUE;

	// Initializes GLUT (and OpenGL)
	glutInit( &argc, argv );

	// Sets the display mode to be a standard image format
	glutInitDisplayMode( GLUT_RGBA );

	// Sets the window size
	glutInitWindowSize( (int)WIDTH, (int)HEIGHT );

	// Sets which major and minor version of OpenGL to use.
	// If 4.x doesn't work, update your video card drivers.
	glutInitContextVersion( 4, 2 );

	// Use the core (non-backwards compatible) version of OpenGL
	glutInitContextProfile( GLUT_CORE_PROFILE );

	// Actually creates the window with the specified title
	glutCreateWindow( "Bitmap Vectorization" );

	// Enable transparency
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//glEnable( GL_BLEND );

	if ( glewInit() != GLEW_OK ) { return -1; }

	// Set line width
	glLineWidth( 3 );
	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	// GLUT will call update() when the main loop is idle
	glutIdleFunc( update );
	
	// GLUT will call draw() when redisplaying the window
	glutDisplayFunc( draw );

	init();

	runAllTests();

	// The main loop for GLUT
	glutMainLoop();
	
	for( unsigned int i = 0; i < vectorizedGraphs.size(); ++i )
	{
		delete vectorizedGraphs[i];
	}
}

/**
 * Initialization
 */
void init()
{
	programIndex = loadShaderProgram( "Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl" );

	if ( programIndex )
	{
		cout << "Shaders loaded correctly!" << endl;
		glUseProgram( programIndex );
	}
	else
		cout << "Shaders did not load correctly." << endl;

	glutKeyboardFunc( onKeyPress );

	/**
	 * Create triangle
	 */
	GLfloat* triVerts = new GLfloat[6];
	triVerts[0] = 0.5f;
	triVerts[1] = 0.0f;
	triVerts[2] = 1.0f;
	triVerts[3] = 1.0f;
	triVerts[4] = 0.0f;
	triVerts[5] = 1.0f;
	adjustVerticesPosition( triVerts, 3 );

	triangle = new Shape( triVerts, 3, programIndex );

	/**
	 * Create rectangle
	 */
	GLfloat* rectVerts = new GLfloat[8];
	rectVerts[0] = 0.0f;
	rectVerts[1] = 0.0f;
	rectVerts[2] = 1.0f;
	rectVerts[3] = 0.0f;
	rectVerts[4] = 1.0f;
	rectVerts[5] = 1.0f;
	rectVerts[6] = 0.0f;
	rectVerts[7] = 1.0f;
	adjustVerticesPosition( rectVerts, 4 );

	rectangle = new Shape( rectVerts, 4, programIndex );

	/**
	 * Create circle
	 */
	GLfloat* circleVerts = new GLfloat[CIRCLE_VERTICES * 2];

	for ( int i = 0; i < CIRCLE_VERTICES * 2; i += 2 )
	{
		circleVerts[i] = 0.5f * std::cos( 2 * PI * i / (float) ( 2 * CIRCLE_VERTICES ) );
		circleVerts[i + 1] = -0.5f * std::sin( 2 * PI * i / (float) ( 2 * CIRCLE_VERTICES ) );
	}
	adjustVerticesPosition( circleVerts, CIRCLE_VERTICES );

	circle = new Shape( circleVerts, CIRCLE_VERTICES, programIndex );
	
	/**
	 * Create semicircle
	 */
	GLfloat* scircleVerts = new GLfloat[CIRCLE_VERTICES + 2];

	for ( int i = 0; i < CIRCLE_VERTICES; i += 2 )
	{
		scircleVerts[i] = 0.5f * std::cos( 2 * PI * i / (float) ( 2 * CIRCLE_VERTICES ) );
		scircleVerts[i + 1] = -0.5f * std::sin( 2 * PI * i / (float) ( 2 * CIRCLE_VERTICES ) );
	}
	scircleVerts[CIRCLE_VERTICES] = -0.5f;
	scircleVerts[CIRCLE_VERTICES + 1] = 0;
	adjustVerticesPosition( scircleVerts, (int)( CIRCLE_VERTICES * 0.5 ) + 1 );

	semicircle = new Shape( scircleVerts, (int)( CIRCLE_VERTICES * 0.5 ) + 1, programIndex );

	/**
	 * Create lines
	 */
	// Up Left
	GLfloat* lineULvertices = new GLfloat[4];
	lineULvertices[0] = 0.0f;
	lineULvertices[1] = 0.0f;
	lineULvertices[2] = -1.0f;
	lineULvertices[3] = -1.0f;
	adjustVerticesPosition( lineULvertices, 2, false );

	lineUpLeft = new Line( lineULvertices, programIndex );
	
	// Up
	GLfloat* lineUvertices = new GLfloat[4];
	lineUvertices[0] = 0.0f;
	lineUvertices[1] = 0.0f;
	lineUvertices[2] = 0.0f;
	lineUvertices[3] = -1.0f;
	adjustVerticesPosition( lineUvertices, 2, false );

	lineUp = new Line( lineUvertices, programIndex );
	
	// Up Right
	GLfloat* lineURvertices = new GLfloat[4];
	lineURvertices[0] = 0.0f;
	lineURvertices[1] = 0.0f;
	lineURvertices[2] = 1.0f;
	lineURvertices[3] = -1.0f;
	adjustVerticesPosition( lineURvertices, 2, false );

	lineUpRight = new Line( lineURvertices, programIndex );
	
	// Left
	GLfloat* lineLvertices = new GLfloat[4];
	lineLvertices[0] = 0.0f;
	lineLvertices[1] = 0.0f;
	lineLvertices[2] = -1.0f;
	lineLvertices[3] = 0.0f;
	adjustVerticesPosition( lineLvertices, 2, false );

	lineLeft = new Line( lineLvertices, programIndex );
	
	// Right
	GLfloat* lineRvertices = new GLfloat[4];
	lineRvertices[0] = 0.0f;
	lineRvertices[1] = 0.0f;
	lineRvertices[2] = 1.0f;
	lineRvertices[3] = 0.0f;
	adjustVerticesPosition( lineRvertices, 2, false );

	lineRight = new Line( lineRvertices, programIndex );
	
	// Down Left
	GLfloat* lineDLvertices = new GLfloat[4];
	lineDLvertices[0] = 0.0f;
	lineDLvertices[1] = 0.0f;
	lineDLvertices[2] = -1.0f;
	lineDLvertices[3] = 1.0f;
	adjustVerticesPosition( lineDLvertices, 2, false );

	lineDownLeft = new Line( lineDLvertices, programIndex );
	
	// Down
	GLfloat* lineDvertices = new GLfloat[4];
	lineDvertices[0] = 0.0f;
	lineDvertices[1] = 0.0f;
	lineDvertices[2] = 0.0f;
	lineDvertices[3] = 1.0f;
	adjustVerticesPosition( lineDvertices, 2, false );

	lineDown = new Line( lineDvertices, programIndex );
	
	// Down Right
	GLfloat* lineDRvertices = new GLfloat[4];
	lineDRvertices[0] = 0.0f;
	lineDRvertices[1] = 0.0f;
	lineDRvertices[2] = 1.0f;
	lineDRvertices[3] = 1.0f;
	adjustVerticesPosition( lineDRvertices, 2, false );

	lineDownRight = new Line( lineDRvertices, programIndex );

	// Set window clear color
	glClearColor( 0.3f, 0.4f, 0.75f, 1.0f );


	// Bitmap Vectorization
	//vectorizedGraphs.push_back( new VectorizedGraph( "Images/test5.raw", 50, 50 ) );
	//vectorizedGraphs.push_back( new VectorizedGraph( "Images/test4.raw", 50, 50 ) );
	vectorizedGraphs.push_back( new VectorizedGraph( "Images/boo.raw", 16, 16 ) );
	vectorizedGraphs.push_back( new VectorizedGraph( "Images/mario.raw", 16, 16 ) );
	vectorizedGraphs.push_back( new VectorizedGraph( "Images/mushroom.raw", 16, 16 ) );
	vectorizedGraphs.push_back( new VectorizedGraph( "Images/goomba.raw", 16, 16 ) );
	vectorizedGraphs.push_back( new VectorizedGraph( "Images/pikachu.raw", 18, 25 ) );


	// Clear memory that was reserved on the heap
	delete[] triVerts;
	delete[] rectVerts;
	delete[] circleVerts;
	delete[] scircleVerts;
	delete[] lineULvertices;
	delete[] lineUvertices;
	delete[] lineURvertices;
	delete[] lineLvertices;
	delete[] lineRvertices;
	delete[] lineDLvertices;
	delete[] lineDvertices;
	delete[] lineDRvertices;
}

/**
 * State updating
 */
void update()
{
	// Tells GLUT's main loop that the screen should be 
	// re-drawn the next time through the loop
	glutPostRedisplay( );
}

/**
 * OpenGL Drawing
 */
void draw()
{
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	// Vectorized Graph
	const int SPACING = 10;
	const int SIZE = 275;
	const int MAX_WIDTH = 3;
	for( unsigned int i = 0; i < vectorizedGraphs.size(); ++i )
	{
		int x = ( SIZE + SPACING ) * ( i % MAX_WIDTH );
		int y = ( SIZE + SPACING ) * ( i / MAX_WIDTH );

		switch( viewState )
		{
			case ViewState::ORIGINAL:
			{
				drawOriginalImage( vectorizedGraphs[i], (float)( x + SPACING ), (float)( y + SPACING), (float)SIZE, (float)SIZE );
				break;
			}
			case ViewState::PLANAR:
			{
				drawPlanarGraph( vectorizedGraphs[i], (float)( x + SPACING ), (float)( y + SPACING), (float)SIZE, (float)SIZE );
				break;
			}
			case ViewState::VECTOR:
			{
				drawVectorizedGraph( vectorizedGraphs[i], (float)( x + SPACING ), (float)( y + SPACING), (float)SIZE, (float)SIZE );
				break;
			}
		}
	}
	
	glFlush( );
}

// Draws a shape using adjusted positions
void drawShape( Shape* shape, float x, float y, float xScale, float yScale )
{
	// Convert from {0, WIDTH or HEIGHT} to {-1, 1}
	x = (2 * x) / (float)WIDTH - 1;
	y = -( (2 * y) / (float)HEIGHT - 1 );

	// Draw the shape based on an adjusted scale and position
	shape->draw( x , y, xScale, yScale );
}

void drawOriginalImage( VectorizedGraph* a_vectorizedGraph, float xOffset, float yOffset, float width, float height )
{
	float nodeWidth = width / (float)a_vectorizedGraph->getWidth();
	float nodeHeight = height / (float)a_vectorizedGraph->getHeight();

	nodeWidth = nodeWidth < 1 ? 1 : nodeWidth;
	nodeHeight = nodeHeight < 1 ? 1 : nodeHeight;

	for( int x = 0; x < a_vectorizedGraph->getWidth(); ++x )
	{
		for( int y = 0; y < a_vectorizedGraph->getHeight(); ++y )
		{
			Color nodeColor = a_vectorizedGraph->getColorAt( x, y );
			float r = nodeColor.getOpenGL_R();
			float g = nodeColor.getOpenGL_G();
			float b = nodeColor.getOpenGL_B();

			float xPos = x * nodeWidth;
			float yPos = y * nodeHeight;

			setShaderColor( programIndex, "color", r, g, b );

			drawShape( rectangle, xOffset + xPos - nodeWidth * 0.5f, yOffset + yPos - nodeHeight * 0.5f, nodeWidth, nodeHeight );
		}
	}
}

void drawVectorizedGraph( VectorizedGraph* a_vectorizedGraph, float xOffset, float yOffset, float width, float height )
{
	float nodeWidth = width / (float)a_vectorizedGraph->getWidth();
	float nodeHeight = height / (float)a_vectorizedGraph->getHeight();

	nodeWidth = nodeWidth < 1 ? 1 : nodeWidth;
	nodeHeight = nodeHeight < 1 ? 1 : nodeHeight;
	
	const float WEIGHT_SCALE = 0.25f;

	for( int x = 0; x < a_vectorizedGraph->getWidth(); ++x )
	{
		for( int y = 0; y < a_vectorizedGraph->getHeight(); ++y )
		{
			Color nodeColor = a_vectorizedGraph->getColorAt( x, y );
			float r = nodeColor.getOpenGL_R();
			float g = nodeColor.getOpenGL_G();
			float b = nodeColor.getOpenGL_B();

			int neighborWeight = a_vectorizedGraph->getNodeAt( x, y )->getNeighborCount() + 1;

			float currentNodeWidth = nodeWidth;// * neighborWeight * WEIGHT_SCALE;
			float currentNodeHeight = nodeHeight;// * neighborWeight * WEIGHT_SCALE;

			float xPos = x * nodeWidth - currentNodeWidth * WEIGHT_SCALE;
			float yPos = y * nodeHeight - currentNodeHeight * WEIGHT_SCALE;

			setShaderColor( programIndex, "color", r, g, b );

			drawShape( circle, xOffset + xPos - currentNodeWidth * 0.5f, yOffset + yPos - currentNodeHeight * 0.5f, currentNodeWidth, currentNodeHeight );
		}
	}
}

void drawPlanarGraph( VectorizedGraph* a_vectorizedGraph, float xOffset, float yOffset, float width, float height )
{
	const float CIRCLE_SCALE_FACTOR = 0.5f;

	float nodeWidth = width / (float)a_vectorizedGraph->getWidth();
	float nodeHeight = height / (float)a_vectorizedGraph->getHeight();

	nodeWidth = nodeWidth < 1 ? 1 : nodeWidth;
	nodeHeight = nodeHeight < 1 ? 1 : nodeHeight;

	for( int x = 0; x < a_vectorizedGraph->getWidth(); ++x )
	{
		for( int y = 0; y < a_vectorizedGraph->getHeight(); ++y )
		{
			Node* pCurrentNode = a_vectorizedGraph->getNodeAt( x, y );

			Color nodeColor = pCurrentNode->getColor();
			float r = nodeColor.getOpenGL_R();
			float g = nodeColor.getOpenGL_G();
			float b = nodeColor.getOpenGL_B();
			
			const float X_POS = xOffset + x * nodeWidth;
			const float Y_POS = yOffset + y * nodeHeight;

			setShaderColor( programIndex, "color", r, g, b );

			for( int i = 0; i < Node::MAX_NEIGHBORS; ++i )
			{
				NeighborDirection direction = NeighborDirection( i );
				bool neighborExists = pCurrentNode->neighborExistsAt( direction );

				if( neighborExists )
				{
					Line* pLine = 0;

					switch( direction )
					{
						case NeighborDirection::TOP_LEFT:
						{
							pLine = lineUpLeft;
							break;
						}
						case NeighborDirection::TOP:
						{
							pLine = lineUp;
							break;
						}
						case NeighborDirection::TOP_RIGHT:
						{
							pLine = lineUpRight;
							break;
						}
						case NeighborDirection::LEFT:
						{
							pLine = lineLeft;
							break;
						}
						case NeighborDirection::RIGHT:
						{
							pLine = lineRight;
							break;
						}
						case NeighborDirection::BOTTOM_LEFT:
						{
							pLine = lineDownLeft;
							break;
						}
						case NeighborDirection::BOTTOM:
						{
							pLine = lineDown;
							break;
						}
						case NeighborDirection::BOTTOM_RIGHT:
						{
							pLine = lineDownRight;
							break;
						}
					}

					if( pLine )
					{
						// Convert from {0, WIDTH or HEIGHT} to {-1, 1}
						//drawShape( pLine, xPos, yPos, nodeWidth, nodeHeight );
						float xPos = (2 * X_POS) / (float)WIDTH - 1;
						float yPos = -( (2 * Y_POS) / (float)HEIGHT - 1 );
						
						pLine->draw( xPos, yPos, nodeWidth, nodeHeight );
						
						drawShape( circle, X_POS - nodeWidth * CIRCLE_SCALE_FACTOR * 0.5f, Y_POS - nodeHeight * CIRCLE_SCALE_FACTOR * 0.5f,
								   nodeWidth * CIRCLE_SCALE_FACTOR, nodeHeight * CIRCLE_SCALE_FACTOR );
					}
				}
			}
		}
	}
}

// Adjusts the position of vertices 
void adjustVerticesPosition( GLfloat* vertices, int totalVertices, bool adjustToTopLeft )
{
	// Find height for the shape
	float widthOffset = vertices[0];
	float heightOffset = vertices[1];
	float minY = vertices[1];
	float maxY = vertices[1];
	float shapeHeight = 0;
	for ( int i = 2; i < totalVertices * 2; i += 2 )
	{
		if ( vertices[i] < widthOffset )
			widthOffset = vertices[i];
		if ( vertices[i + 1] > heightOffset )
			heightOffset = vertices[i + 1];

		if ( vertices[i + 1] > maxY )
			maxY = vertices[i + 1];
		if ( vertices[i + 1] < minY )
			minY = vertices[i + 1];
	}
	shapeHeight = maxY - minY;

	for ( int i = 0; i < totalVertices * 2; i += 2 )
	{
		// Convert from {0, WIDTH or HEIGHT} to {-1, 1}
		if( adjustToTopLeft )
		{
			vertices[i] = ( 2 * ( vertices[i] - widthOffset ) ) / (float)WIDTH;
			vertices[i + 1] = -( 2 * (vertices[i + 1] - heightOffset + shapeHeight ) ) / (float)HEIGHT;
		}
		else
		{
			vertices[i] = ( 2 * ( vertices[i] ) ) / (float)WIDTH;
			vertices[i + 1] = -( 2 * vertices[i + 1] ) / (float)HEIGHT;
		}
	}
}

void onKeyPress( unsigned char keyCode, int x, int y )
{
	if( keyCode == ' ' )
	{
		viewState = ViewState( ( viewState + 1 ) % ( ViewState::LENGTH ) );
	}
}