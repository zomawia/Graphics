#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(800, 800);
	Texture tex = loadTexture("../../resources/textures/spritesheet.png");
	int index[] = {12,13,14,15,8,9,10,11,4,5,6,7,0,1,2,3};
	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1,1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	Shader sq = loadShader	(
		"../../resources/shaders/test.vert", 
		"../../resources/shaders/test.frag");

	Framebuffer screen = { 0,800,800 };

	while (context.step())
	{
		//glm::mat4 rot = glm::rotate((float)time*60, glm::vec3(.25, .25, 1));

		clearFramebuffer(screen);

		int loc = 0, tslot = 0;
		setUniforms(sq, loc, tslot, tex, index[2]);

		//printf("Time: %f \n", dt);

		s0_draw(screen, sq, cube);
	}

	context.exit();
	return 0;
}
