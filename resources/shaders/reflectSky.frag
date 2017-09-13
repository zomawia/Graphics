#version 450

out vec4 FragColor;

in vec3 n;
in vec4 p;
in vec3 cameraPos;

layout(location = 3) uniform samplerCube skybox;

void main()
{             
    vec3 I = normalize(p.xyz - cameraPos);
	vec3 R = reflect(I, normalize(n));
	
	FragColor = vec4(texture(skybox, R).rgb, 1.0);
}  