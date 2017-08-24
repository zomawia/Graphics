
#version 450
layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;
layout(location = 1) uniform int index;
out vec2 vUV;
void main ()
{ 	
	int rows = 4;
	int cols = 4;

	int c = index / rows;
	int r = index % cols;

	vec2 spriteUV = (texCoord + vec2(r,c)) / vec2(rows, cols);
	
	gl_Position = position; 	
	vUV = spriteUV; 
}