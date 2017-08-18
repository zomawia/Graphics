#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"

int main() {
	Context context;
	context.init();

	///////////////////////////////
	Vertex verts[9] =
	{
		{ { -.75f,-.5f, 0, 1 },{ 1,0,0,1 } },
		{ { -.25f, .5f, 0, 1 },{ 0,1,0,1 } },
		{ { .75,  .15f, 0, 1 },{ 1,0,1,1 } },
		{ { .75f,-.5f, 0, 1 },{ 0,1,1,1 } },
		{ { -.5f,.5f, 0, 1 },{ 1,0,0,1 } },
		{ { -.75f, .45f, 0, 1 },{ 0,1,0,1 } },
		{ { .35,  -.2f, 0, 1 },{ 1,0,1,1 } },
		{ { .55,  .5f, 0, 1 },{ 1,0,1,1 } },
		{ { -.5f,-.5f, 0, 1 },{ 0,1,1,1 } }
	};

	unsigned idxs[9] = { 0,1,2,3,4,5,6,7,8 };

	Geometry g = makeGeometry(verts, 9, idxs, 9);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 0) uniform float time;\n"
		"out vec4 vColor;\n"
		"void main () { vColor = color; gl_Position = position; gl_Position.x += sin(time)/5.0; }\n";

	const char* fsource =
		"#version 450\n"
		"in vec4 vColor;\n"
		"out vec4 outColor;\n"
		"void main () { outColor = vColor; }\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 800 };
	//////////////////////////////////////

	while (context.step()) {
		clearFramebuffer(f);
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 0, context.getKey(32));
		s0_draw(f, s, g);		
	}

	freeGeometry(g);
	freeShader(s);

	context.exit();
	return 0;
}