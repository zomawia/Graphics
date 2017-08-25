#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(800, 600);

	Geometry sphere = loadGeometry("../../resources/models/sphere.obj");
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture coolguy = loadTexture("../../resources/textures/coolguy.jpg");
	Shader mvplite = loadShader("../../resources/shaders/mvplite.vert",
		"../../resources/shaders/mvplite.frag");
	
	Framebuffer screen = { 0,800,600 };

	glm::vec3 targetPosition = glm::vec3(0, 0, 0);

	while (context.step())
	{
		float time = context.getTime();

		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 4, -3), targetPosition, glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

		glm::mat4 go_model0; // identity matrix for now
		
		glm::mat4 go_model1 = glm::translate(glm::vec3(0, .5, 0)) * 
			glm::rotate(sin(time), glm::vec3(1, 0, 0)) * 
			glm::scale(glm::vec3(sin(time), sin(time), sin(time))) * 
			go_model0;

		glm::mat4 go_model2 = glm::translate(glm::vec3(sin(time), 0, sin(time))) * go_model0;

		glm::mat4 go_model3 = glm::translate(glm::vec3(sin(time), -.2, -sin(time))) * go_model0;;

		glm::mat4 go_coolguy = glm::translate(glm::vec3(0, 0, 0)) *
			glm::rotate(time, glm::vec3(0, 1, 0)) *
			glm::scale(glm::vec3(2, 1, 4)) * go_model0;


		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);		

		targetPosition.x += context.getKey('A') | -context.getKey('D');
		targetPosition.y += context.getKey('W') | -context.getKey('S');
		targetPosition.z += context.getKey('Q') | -context.getKey('E');
		
		int loc = 0, tslot = 0;
		setUniforms(mvplite, loc, tslot, cam_proj, cam_view, go_coolguy, coolguy);
		s0_draw(screen, mvplite, sphere);

		loc = 0, tslot = 0;
		setUniforms(mvplite, loc, tslot, cam_proj, cam_view, go_model3, ss_diffuse);
		s0_draw(screen, mvplite, ss_geo);

		loc = 0, tslot = 0;
		setUniforms(mvplite, loc, tslot, cam_proj, cam_view, go_model1, ss_diffuse);
		s0_draw(screen, mvplite, ss_geo);

		loc = 0, tslot = 0;
		setUniforms(mvplite, loc, tslot, cam_proj, cam_view, go_model2, ss_diffuse);
		s0_draw(screen, mvplite, ss_geo);
	}


	context.exit();
	return 0;
}