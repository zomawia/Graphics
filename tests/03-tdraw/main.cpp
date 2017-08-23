#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"

int main() 
{
	Context context;
	context.init();	

	const double PI = 3.14159265359;

	Vertex verts[9] =
	{
		{ { -.75f,-.75f, .5, 1 },{ 0,1,0,1 },{ 0,1 } },
		{ { .75f,-.75f, .5, 1 },{ 1,1,0,1 },{ 1,1 } },
		{ { .75f,.75f, .5, 1 },{ 0,1,1,1 },{ 1,0 } },
		{ { -.75f,.75f, .5, 1 },{ 1,0,1,1 },{ 0,0 } },
	};

	unsigned idxs[3*2] = { 0,1,2, 0,2,3 };

	Geometry g = makeGeometry(verts, 6, idxs, 18);

	unsigned char pixels[] = { 255,0,128,255,
		255,128,255,0,
		0,255,128,255,
		255,128,255,0 };

	Texture t_mask = makeTexture(4, 4, 1, pixels);
	Texture t_magyel = makeTexture(4, 1, 3, pixels);


	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 2) in vec2 uv;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"		
		"gl_Position = position;\n"
		"vUV = uv;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;\n"
		"layout(location = 0) uniform sampler2D map;\n"
		"layout(location = 1) uniform float time;\n"
		"layout(location = 2) uniform int key;\n"
		"void main ()\n"
		"{\n"
		"outColor = 2*key - texture(map, vUV)*sin(time);\n"		
		"}\n";

	Shader s = makeShader(vsource, fsource);
	Framebuffer f = { 0, 800, 800 };

	while (context.step()) {
		int loc = 0; int tex = 0;
		setUniforms(s, loc, tex, t_magyel,
			(float)context.getTime(), context.getKey(' '));
		s0_draw(f, s, g);			
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	freeTexture(t_mask);
	context.exit();
	return 0;
}