#version 450

in vec2 vUV;

layout(location = 2) uniform mat4 lproj;
layout(location = 3) uniform mat4 lview;

layout(location = 4) uniform vec4 lightColor;
layout(location = 5) uniform float intensity;

layout(location = 6) uniform sampler2D normalMap;
layout(location = 7) uniform sampler2D positionMap;
layout(location = 8) uniform sampler2D shadowMap;

layout(location = 0) out vec4 outDiffuse;
layout(location = 1) out vec4 outSpecular;

void main()
{
	vec3 L = (view * -lightView[2]).xyz;
	vec3 N = texture(normalMap, vUV).xyz;	

	float lamb = max(0, dot(-L, N));
	
	outDiffuse = lightColor * intensity * lamb;
}