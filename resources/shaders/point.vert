#version 450

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec3 inVelocity;
layout(location = 2) in vec4 inColor;

out vec4 inoutColor;

layout(location = 0) uniform mat4 l_proj;
layout(location = 1) uniform mat4 l_view;
layout(location = 2) uniform mat4 model;

layout(location = 4) uniform float time;

void main()
{
	inoutColor = inColor;
	gl_Position = l_proj * l_view * model * inPosition;	
	gl_PointSize = 1.75f;
}