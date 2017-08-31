#version 450

in vec2 vUV;
in vec4 vPos;

in mat4 vTBN;

out vec4 outColor;

layout (location = 1) uniform mat4 view;
layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform sampler2D normal;
layout (location = 5) uniform vec3 lightPos;
layout (location = 6) uniform vec4 lightColor;

float lambert(vec3 N, vec3 L)
{
	return max(0, dot(N, -L));
}

float phong(vec3 N, vec3 L, vec3 V, float power)
{
	vec3 R = reflect(L, N);	
	float base = max(0, dot(V, R));
	return pow(base, power);
}

void main()
{
    
    vec4 tN = 1-2*texture(normal, vUV);
	tN.a = 0;
	tN = normalize(tN);

	vec3 N = (vTBN * tN).xyz;
	vec3 V = view[2].xyz;

	float spec = phong(N, lightPos ,V, 0.8);
	float lam = lambert(N, lightPos);
	

    outColor += texture(diffuse, vUV) * lam +
				(vec4(1,1,1,1) * spec);
}