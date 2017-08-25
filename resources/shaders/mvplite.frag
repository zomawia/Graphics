#version 450

flat in vec2 vUV;

layout (location = 3) uniform sampler2D diffuse;

out vec4 outColor;

void main()
{
    outColor = texture(diffuse, vUV);	
}