#version 450

/**
* Use the location the same as in compute shader for
* easy getting attribute pointers address.
*/
layout(location = 0) in vec4 inPosition;
layout(location = 2) in vec4 inColor;

out vec4 inoutColor;

layout(location = 0) uniform mat4 l_proj;
layout(location = 1) uniform mat4 l_view;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform float pointSize;

void main()
{
	/// Simply pass the color next and set the vertex position and size.
	inoutColor = inColor;
	gl_Position = l_proj * l_view * model * inPosition;
	gl_PointSize = pointSize;
}