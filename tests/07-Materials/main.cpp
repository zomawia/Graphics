#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(1280,720,"poop");

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Framebuffer screen = { 0, 1280, 720 };
	Shader standard = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");

	////////////////////////
	/// Model Data
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;

	Texture   ss_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture   ss_diffuse = loadTexture("../../resources/textures/coolcat.jpg");
	Texture   ss_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float     ss_gloss = 8;

	//////////////////////////
	// Camera Data
	glm::mat4 cam_view = glm::lookAt(
		glm::vec3(0, 2, 3),
		glm::vec3(0, 2, 0),
		glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 5.f);

	//////////////////////////
	// Light
	glm::vec3 l_dir = glm::normalize(glm::vec3(.2, -1, -1));
	glm::vec4 l_color = glm::vec4(1.0, .5, 1.0, 1);
	float     l_intensity = 4.0;
	glm::vec4 l_ambient = glm::vec4(.2, .5, .1, 1);
	int		  l_type = 0;	

	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);

	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
								   "../../resources/shaders/quad.frag");
	unsigned key = 0, key2 = 1;
	while (context.step())
	{
		float time = context.getTime();
		float time2 = context.getTime();
		ss_model = glm::rotate(time, glm::vec3(1, 1, 0));

		////////////////////
		// frame buffer pass
		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam_proj, cam_view,	// Camera data!
			ss_model, ss_diffuse, ss_specular, ss_normal, ss_gloss, // model data!
			l_dir, l_color, l_intensity, l_ambient, l_type		  // light data!
		);

		s0_draw(fBuffer, standard, ss_geo);
		
		////////////////
		// screen pass	
		clearFramebuffer(screen);
		loc = 0, slot = 0;
		setUniforms(fsq_shader, loc, slot, fBuffer.targets[key], fBuffer.targets[key2], time);
		s0_draw(screen, fsq_shader, quad);

		if (time > .1)
		{
			context.setTime(0.0);
			key++;
			if (key > 3)
				key = 0;
		}

		if (time2 > .1)
		{
			context.setTime(0.0);
			key2++;
			if (key2 > 3)
				key2 = 0;
		}
		
	}

	context.exit();
	return 0;
}