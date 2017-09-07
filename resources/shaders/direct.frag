#version 450

layout(location = 3) uniform mat4 lproj;
layout(location = 4) uniform mat4 lview;
layout(location = 5) uniform sampler2D shadowmap;
layout(location = 6) uniform mat4 lproj2;
layout(location = 7) uniform mat4 lview2;
layout(location = 8) uniform sampler2D shadowmap2;
layout(location = 9) uniform sampler2D diffuseMap;


in vec2 vUV;
in vec4 vPos;

uniform float shadowBias = 0.01;

// Simple matrix that converts from clip space (-1,1) to UV space (0,1)
uniform mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
							 0.0f, 0.5f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.5f, 0.0f,
							 0.5f, 0.5f, 0.5f, 1.0f);

out vec4 outColor;

float pcf(in sampler2D map, in vec4 shadowPosition, int iterations);

void main()
{
	vec4 sUV = clipToUV * lproj * lview * vPos;
	vec4 sUV2 = clipToUV * lproj2 * lview2 * vPos;
	
	float visibility = 1;
	if(texture(shadowmap,sUV.xy).r  < sUV.z - shadowBias)
		visibility = 0;	

	float visibility2 = 1;
	if(texture(shadowmap2,sUV.xy).r  < sUV2.z - shadowBias)
		visibility = .50;	
				
	outColor = texture(diffuseMap, sUV.xy) * visibility * texture(diffuseMap, sUV2.xy);
	//gl_FragColor = outColor;
}

// takes in shadow map and a proj. fragment position to determine
// how much in shadow we are based upon the number of iterations
float pcf(in sampler2D map, in vec4 shadowPosition, int it)
{
	vec2 sDim = textureSize(map,0).xy;
	float retval;

	vec2 uv = shadowPosition.xy;
	float z = shadowPosition.z - 0.01;


	for (int i = -it; i <= it; ++i)
	{
		if (!(texture(map, uv + vec2(i,0)/sDim).r < z))
			retval++;
		if (!(texture(map, uv + vec2(0,i)/sDim).r < z))
			retval++;
	}

	return retval / (it * 4);
}
