// Request GLSL 3.3
#version 330

in vec3 inPosition;

void main()
{
	gl_Position = vex4(inPosition, 1.0);
}