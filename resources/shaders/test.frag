#version 450

layout(location = 0) uniform sampler2D map;
//layout(location = 1) uniform float time;

out vec4 outColor;
in vec2 vUV;

void main () 
{ 
	outColor = texture(map, vUV.xy);
};