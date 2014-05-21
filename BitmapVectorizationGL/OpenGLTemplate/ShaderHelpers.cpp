#include "ShaderHelpers.h"
#include <iostream>
#include <fstream>

using namespace std;

char* loadTextFile( const char* file )
{
	ifstream inFile( file, ios::binary );

	if ( inFile.is_open() )
	{
		inFile.seekg( 0, ios::end );
		int length = (int)inFile.tellg();

		inFile.seekg( 0, ios::beg );

		char* fileContents = new char[ length + 1 ];
		inFile.read( fileContents, length );

		fileContents[ length ] = 0;

		// Close the file and clear up memory that was used
		// to hold the file contents
		inFile.close();

		return fileContents;
	}
	else
		return 0;
}

GLuint loadShader( const char* file, GLenum shaderType )
{
	const char* fileContents = loadTextFile( file );

	if ( !fileContents )
	{
		cout << "There was an error opening the file." << endl;
		return 0;
	}

	GLuint shaderIndex = glCreateShader( shaderType );
	glShaderSource( shaderIndex, 1, &fileContents, 0 );
	glCompileShader( shaderIndex );
	
	delete[] fileContents;

	// Determine if shader compiled
	GLint compilationResult;
	glGetShaderiv( shaderIndex, GL_COMPILE_STATUS, &compilationResult );

	if ( compilationResult == GL_TRUE )
	{
		cout << "Successful compilation." << endl;
		return shaderIndex;
	}
	else
	{
		cout << "Failed to compile." << endl;

		GLint logLength;

		// Get length of log
		glGetShaderiv( shaderIndex, GL_INFO_LOG_LENGTH, &logLength );

		// Get the log
		char* log = new char[ logLength ];
		glGetShaderInfoLog( shaderIndex, logLength, 0, log );

		cout << log << endl;

		glDeleteShader( shaderIndex );

		delete[] log;

		return -1;
	}
}

GLuint loadShaderProgram( const char* vertexFile, const char* fragmentFile )
{
	GLuint vertexShaderIndex = loadShader( vertexFile, GL_VERTEX_SHADER );

	if ( !vertexShaderIndex )
		return 0;
	
	GLuint fragmentShaderIndex = loadShader( fragmentFile, GL_FRAGMENT_SHADER );

	if ( !fragmentShaderIndex )
		return 0;

	// Create the shader program if the shaders were loaded correctly
	GLuint programID = glCreateProgram();
	glAttachShader( programID, vertexShaderIndex );
	glAttachShader( programID, fragmentShaderIndex );
	glLinkProgram( programID );

	// Determine if the program linked correctly
	GLint linkResult;
	glGetProgramiv( programID, GL_LINK_STATUS, &linkResult );

	if ( linkResult == GL_TRUE )
		return programID;
	else
	{
		int errorLogLength;
		glGetProgramiv( programID, GL_INFO_LOG_LENGTH, &errorLogLength );

		char* errorLog = new char[ errorLogLength ];
		glGetProgramInfoLog( programID, errorLogLength, 0, errorLog );

		cout << errorLog;

		glDeleteProgram( programID );

		delete[] errorLog;

		return -1;
	}
}

void setShaderColor( GLuint programIndex, const char* uniformVariableName, float r, float g, float b, float a )
{
	// Get location of specified variable in the specified shader program
	GLint uniformLocation = glGetUniformLocation( programIndex, uniformVariableName );

	glProgramUniform4f( programIndex, uniformLocation, r, g, b, a );
}


void setShaderVec2( GLuint programIndex, const char* uniformVariableName, vec2 vecToSend )
{
	// Get location of specified variable in the specified shader program
	GLint uniformLocation = glGetUniformLocation( programIndex, uniformVariableName );

	glProgramUniform2fv( programIndex, uniformLocation, 1, &vecToSend[0] );
}