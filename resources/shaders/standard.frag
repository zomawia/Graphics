#version 450

in vec2 vUV;
in vec4 vPos;

in mat4 vTBN;

out vec4 outColor;

layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform vec3 lightPos;
layout (location = 5) uniform vec4 lightColor;

void main()
{
    vec4 surfaceColor = texture(diffuse, vUV);
    
	vec3 vNormal = vPos.xyz;

    float lambertianFactor = max(dot(vNormal, -lightPos), 0);

    vec4 lambertianTerm = surfaceColor * lambertianFactor * lightColor;


    outColor = lambertianTerm;
}