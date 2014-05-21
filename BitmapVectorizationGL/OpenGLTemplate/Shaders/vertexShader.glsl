#version 330

layout (location = 0) in vec2 position;

uniform vec2 offset;
uniform vec2 scale;

void main()
{
	gl_Position = vec4(position * scale + offset, 0, 1);
}