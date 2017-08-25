
#version 450

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 normal;

layout(location = 1) uniform mat4 rot;

flat out vec4 vCol;
out vec2 vUV;
out vec4 vNormal;

void main ()
{ 			
	//vCol = col; 
	vUV = texCoord;
	vNormal = rot * normal;
	gl_Position = rot * pos; 	
}