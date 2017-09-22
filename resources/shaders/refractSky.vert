#version 450

layout(location = 0) in vec4 position;
layout(location = 3) in vec4 normal;

layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;
layout(location = 4) uniform float time;

out vec4 p;
out vec3 n;
out vec3 cameraPos;

void main()
{	
	cameraPos = proj[0].xyz;
	vec4 pos = position;
	n = mat3(transpose(inverse(model))) * normal.xyz;
	p = model * position;		

	pos.x = sin(time * pos.x);
	
	gl_Position = proj * view * model * pos;
}