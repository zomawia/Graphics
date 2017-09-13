#version 450

layout(location = 0) in vec4 position;
layout(location = 3) in vec4 normal;

layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

out vec4 p;
out vec3 n;
out vec3 cameraPos;

void main()
{	
	cameraPos = proj[0].xyz;
	
	n = mat3(transpose(inverse(model))) * normal.xyz;
	p = model * position;		
	gl_Position = proj * view * model * position;
}