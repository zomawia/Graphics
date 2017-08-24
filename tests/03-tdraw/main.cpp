#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"
#include "glm\ext.hpp"

int main() 
{
	Context context;
	context.init(800,800);	

	const double PI = 3.14159265359;

	Vertex verts[4] =
	{
		{ { -.75f,-.75f, .5, 1 },{ 1,1,1,1 },{ 0,1 } },
		{ { .75f,-.75f, .5, 1 },{ 1,1,1,1 },{ 1,1 } },
		{ { .75f,.75f, .5, 1 },{ 1,1,1,1 },{ 1,0 } },
		{ { -.75f,.75f, .5, 1 },{ 1,1,1,1 },{ 0,0 } },
	};

	unsigned idxs[3*2] = { 0,1,2, 0,2,3 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);

	unsigned char pixels[] = 
		{ 255,255,255,255,
		0,0,0,255,
		0,0,0,255,
		0,0,0,255 };

	//Texture t_mask = makeTexture(4, 4, 1, pixels);
	Texture t_magyel = makeTexture(4, 4, 4, pixels);


	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 5) uniform mat4 model;\n"
		"layout(location = 2) in vec2 uv;\n"
		"out vec4 vColor;\n"
		"out vec2 vUV;\n"

		"void main ()\n"
		"{\n"		
		"gl_Position = model * position;\n"
		"vUV = uv;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"

		"out vec4 outColor;\n"

		"in vec4 vColor;\n"
		"in vec2 vUV;\n"

		"layout(location = 0) uniform sampler2D map;\n"
		"layout(location = 1) uniform float time;\n"
		"layout(location = 2) uniform int R;\n"
		"layout(location = 3) uniform int G;\n"
		"layout(location = 4) uniform int B;\n"

		"vec4 RED = vec4(1,0,0,1);\n"
		"vec4 GREEN = vec4(0,1,0,1);\n"
		"vec4 BLUE = vec4(0,0,1,1);\n"
		
		"void main ()\n"
		"{\n"		
		"if (R == 1)\n"		
		"outColor += texture(map, vUV) + RED;\n"
		"else if (G == 1)\n"
		"outColor += texture(map, vUV) + GREEN;\n"
		"else if (B == 1)\n"
		"outColor += texture(map, vUV) + BLUE;\n"
		"else\n"
		"outColor += texture(map, vUV);\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);
	Framebuffer f = { 0, 800, 800 };

	while (context.step()) {		
		
		float time = context.getTime();
		bool R = context.getKey('R');
		bool G = context.getKey('G');
		bool B = context.getKey('B');
		
		clearFramebuffer(f);
		
		glm::mat4 mod1 = glm::rotate((float)context.getTime(), glm::vec3(1.2, .5, 1.8));
		glm::mat4 mod2 = glm::rotate((float)context.getTime(), glm::vec3(1, 2.7, 1)) * glm::scale(glm::vec3(.2, .5, .7));		
		
		int loc = 0; int tex = 0;
		setUniforms(s, loc, tex, t_magyel, time, R,G,B, mod1);		
		s0_draw(f, s, g);			

		loc = 0; tex = 0;
		setUniforms(s, loc, tex, t_magyel, time, R, G, B, mod2);
		s0_draw(f, s, g);
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	

	context.exit();

	return 0;
}