#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\GameObjects.h"
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
	// Model Data
	SpecGloss specgloss[2];
	specgloss[0].geo = loadGeometry("../../resources/models/soulspear.obj");
	specgloss[0].model;

	specgloss[0].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	specgloss[0].diffuse = loadTexture("../../resources/textures/coolcat.jpg");
	specgloss[0].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	specgloss[0].gloss = 8;

	//////////////////////////
	// Camera Data
	Camera cam;
	cam.view = glm::lookAt(
		glm::vec3(0, 2, 3),
		glm::vec3(0, 2, 0),
		glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 5.f);

	//////////////////////////
	// Light
	StandardLight l;
	l.dir		= glm::normalize(glm::vec3(.2, -1, -1));
	l.color		= glm::vec4(1.0, .5, 1.0, 1);
	l.intensity = 4.0;
	l.ambient	= glm::vec4(.2, .5, .1, 1);
	l.type		= 0;	

	Framebuffer fBuffer = makeFramebuffer(1280, 720, 4, true, 3, 1);

	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
								   "../../resources/shaders/quad.frag");
	unsigned key = 0, key2 = 1;
	while (context.step())
	{
		float time = context.getTime();
		float time2 = context.getTime();
		specgloss[0].model = glm::rotate(time, glm::vec3(1, 1, 0));

		////////////////////
		// frame buffer pass
		clearFramebuffer(fBuffer);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, slot = 0;
		setUniforms(standard, loc, slot,
			cam.proj, cam.view,	// Camera data!
			specgloss[0].model, specgloss[0].diffuse, specgloss[0].specular, 
			specgloss[0].normal, specgloss[0].gloss, // model data!
			l.dir, l.color, l.intensity, l.ambient, l.type		  // light data!
		);

		s0_draw(fBuffer, standard, specgloss[0].geo);
		
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