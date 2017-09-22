#version 450

out vec4 outColor;
in vec4 inoutColor;

layout(location = 3) uniform sampler2D map;

void main()
{
    outColor = texture(map, inoutColor.xy);
}