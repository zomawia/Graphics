#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(1600, 800);	

	Texture coolguy = loadTexture("../../resources/textures/coolguy.jpg");
	Texture coolgirl = loadTexture("../../resources/textures/coolgirl.jpg");
	Texture coolcat = loadTexture("../../resources/textures/coolcat.jpg");
	Geometry cube = loadGeometry("../../resources/models/sphere.obj");

	Shader cubeShader = loadShader(
		"../../resources/shaders/cube.vert",
		"../../resources/shaders/cube.frag");

	Framebuffer screen = { 0,1600,800 };

	setFlags(RenderFlag::DEPTH);

	while (context.step())
	{		
		clearFramebuffer(screen,true,true);

		float time = context.getTime();

		glm::mat4 sun = glm::scale(glm::vec3(.3,.3,.3) ) * 
			glm::rotate(time, glm::vec3(1, 0, 1) );

		glm::mat4 planet = sun * glm::translate(glm::vec3(1,1,1));

		glm::mat4 moon = planet * glm::translate(glm::vec3(1, 1, 1));

		int loc = 0, tslot = 0;
		setUniforms(cubeShader, loc, tslot, coolguy, sun);
		s0_draw(screen, cubeShader, cube);

		loc = 0, tslot = 0;
		setUniforms(cubeShader, loc, tslot, coolgirl, planet);
		s0_draw(screen, cubeShader, cube);

		loc = 0, tslot = 0;
		setUniforms(cubeShader, loc, tslot, coolcat, moon);
		s0_draw(screen, cubeShader, cube);

	}

	context.exit();
	return 0;
}
