#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(1280, 800);

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1,1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};


	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Shader standard = loadShader("../../resources/shaders/standard.vert", 
									"../../resources/shaders/standard.frag");

	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");

	Texture floor_diffuse = loadTexture("../../resources/textures/coolcat.jpg");
	Texture floor_normal = loadTexture("../../resources/textures/soulspear_normal.tga");

	Framebuffer screen = { 0, 1280, 800 };
	glm::mat4 proj = glm::perspective(45.f, 1280.f / 800.f, 0.01f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 2, -2),
		glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	glm::vec4 lightCol = glm::vec4(1, 1, 1, 1);
	glm::vec3 lightDir = glm::normalize(glm::vec3(3, -5, 1));

	while (context.step())
	{
		float time = context.getTime();
		glm::mat4 model = glm::rotate(time, glm::vec3(0, 1, 0));
		glm::mat4 modquad = glm::rotate(time, glm::vec3(1, -1, 0));
		
		glm::mat4 modquad0 = glm::rotate(
			glm::radians(90.f),
			glm::vec3(-1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));
		glm::mat4 modquad1 = glm::rotate(time * 2, glm::vec3(0, 1, 0));
		glm::mat4 modquad2 = glm::rotate(time * 5, glm::vec3(0, -1, 1));
		glm::mat4 modquad3 = modquad * glm::translate(glm::vec3(5, -5, 0));
		glm::mat4 modquad4 = modquad * glm::translate(glm::vec3(5, 0, 0));
		glm::mat4 modquad5 = modquad * glm::translate(glm::vec3(-5, 0, 0));
		glm::mat4 modquad6 = modquad * glm::translate(glm::vec3(-5, 5, 0));

		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, model, ss_diffuse, ss_normal, lightDir, lightCol);
		s0_draw(screen, standard, ss_geo);

		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);

		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad0, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);

		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad1, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);

		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad2, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);

		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad3, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);
		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad4, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);
		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad5, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);
		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad6, floor_diffuse, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);

		loc = 0, slot = 0;
		setUniforms(standard, loc, slot, proj, view, modquad, floor_normal, floor_normal, lightDir, lightCol);
		s0_draw(screen, standard, quad);
	}

	context.exit();
	return 0;
}