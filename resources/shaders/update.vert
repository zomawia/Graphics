#version 450

// Lots of code borrowed from:
// http://prideout.net/blog/?tag=opengl-transform-feedback

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 vel;
layout(location = 2) in vec4 col;

out vec4 outPos;
out vec3 outVel;
out vec4 outCol;

layout(location = 0) uniform float time;

vec3 position = pos.xyz;
vec3 velocity = vel;
vec4 color = col;



void main()
{	
	position = sin(time * velocity);	

	if (position.x > .9 || position.x < -.9 || position.y > .9 || position.y < -.9)
	{
		position = vec3(0);
	}
	
	if (position.x > 0.5f)
	{	
		position = tan(time/2 * velocity);
	}

	if (position.x < -0.5f)
	{	
		position = tan(time/2 * velocity);
	}

	if (position.y > 0.5f)
	{	
		position = cos(time/2 * velocity);
	}

	if (position.y < -0.5f)
	{	
		position = -cos(time/2 * velocity);
	}

	outPos = vec4(position, 1);
	outVel = velocity;	
	outCol = color;
}