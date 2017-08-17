#include "graphics\Context.h"
#include "graphics\\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"


int main() {
	Context context;
	context.init();		
	size_t color = 0;
	///////////////////////////////
	Vertex verts[4] = 	
	{ 
		{ { -.75f,-.5f, 0, 1 } },
		{ { -.75f, .5f, 0, 1 } },
		{ {  .75,  .5f, 0, 1 } },
		{ {  .75f,-.5f, 0, 1 } }
	};

	unsigned idxs[6] = { 0,1,2,0,2,3 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"out vec4 vPos;\n"
		"void main ()\n"
		"{ vPos = position;\n"
		"gl_Position = position;}\n";

	const char* fsource =
		"#version 450\n"
		"in vec4 vPos;\n"
		"out vec4 outColor;\n"
		"void main () { outColor = 1.0 - vPos; }\n";

	//const char* vsource =
	//	"#version 450\n"
	//	"layout(location = 0) in vec4 position;\n"
	//	"void main () { gl_Position = position; }\n";

	//const char* fsource =
	//	"#version 450\n"
	//	"out vec4 outColor;\n"
	//	"void main () { outColor = vec4(1.0, 1.0, 0.0, 1.0); }\n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };
	//////////////////////////////////////


	while (context.step()) {		
		s0_draw(f, s, g);		
	}

	freeGeometry(g);
	freeShader(s);

	context.exit();
	return 0;
}