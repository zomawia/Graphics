#version 450

out vec4 FragColor;

in vec3 n;
in vec4 p;
in vec3 cameraPos;

layout(location = 3) uniform samplerCube skybox;

void main()
{             
    float ratio = 1.00 / 1.42;
	vec3 I = normalize(p.xyz - cameraPos);
	vec3 R = refract(I, normalize(n), ratio);
	
	FragColor += vec4(texture(skybox, R).rgb, 1.0);
}  