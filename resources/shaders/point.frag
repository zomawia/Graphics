#version 450

in vec2 vUV;
in vec3 vNormal;
in vec3 vPos;

layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform vec3 lightPos;
layout (location = 5) uniform vec4 lightColor;

out vec4 outColor;

void main()
{
    vec4 surfaceColor = texture(diffuse, vUV);

	vec3 DISP = vPos - lightPos;

	float d = length(DISP);
	float a = 8.0/(d*d);
	vec3 L = normalize(DISP);
	vec3 N = vNormal;

    // max will clamp the factor so it doesn’t go negative.
    float lambertianFactor = max(0, dot(N, -L)) * a;

    vec4 lambertianTerm = 
		surfaceColor * lambertianFactor * lightColor;

    outColor = lambertianTerm;
}