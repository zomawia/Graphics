#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texcoord;

layout(location = 2) uniform float time;

out vec2 vUV;
vec4 vPos;

void main()
{
	vPos = position;


	gl_Position = vPos;

	vUV = texcoord;
}

