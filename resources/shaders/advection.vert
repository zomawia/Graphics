#version 450

layout(location = 0) uniform float time;

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 vel;
layout(location = 2) in vec4 col;

out vec4 outPos;
out vec3 outVel;
out vec4 outCol;

void main()
{	
    vec3 eye = vec3(0.0,0.0,4.0);
    float dist = length(pos.xyz - eye);
	
	gl_Position.x = sin(time);

	outPos = pos;
	outVel = vel;	
	outCol = col;
}