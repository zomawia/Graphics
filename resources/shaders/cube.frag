#version 450

layout(location = 0) uniform sampler2D map;

flat in vec4 vCol;
in vec2 vUV;
in vec4 vNormal;

out vec4 outColor;

void main () 
{ 	
	//outColor = texture(map, vUV);
	outColor = dot(vNormal, -normalize(vec4(1,0,1,0))) * texture(map, vUV);
	//outColor.a = 1;
};