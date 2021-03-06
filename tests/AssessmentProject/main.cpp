///////////////////////////////////////////////////////////////////////
//		Zomawia Sailo
//		Graphics Library Assessment Project
//	Planned library extensions
//	1. Cube-mapping support
//		- skyboxes
//		- reflection shader
//		- refraction shader
//	2. Transform feedback
//		- particle system
///////////////////////////////////////////////////////////////////////

#include "graphics\GameObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"
#include <cstdlib>

float r2(float min, float max)
{
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

void main()
{
	Context context;
	context.init(1280, 720);
	


	Geometry cubeGeo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 model;

	Texture coolcat = loadTexture("../../resources/textures/coolcat.jpg");

	CubeTexture cubeMap = loadCubeMap(				
		"../../resources/textures/stormydays_ft.tga",
		"../../resources/textures/stormydays_bk.tga",
		"../../resources/textures/stormydays_up.tga",
		"../../resources/textures/stormydays_dn.tga",		
		"../../resources/textures/stormydays_rt.tga",
		"../../resources/textures/stormydays_lf.tga"
		);

	CubeTexture cityMap = loadCubeMap(
		"../../resources/textures/sincity_ft.tga",
		"../../resources/textures/sincity_bk.tga",

		"../../resources/textures/sincity_up.tga",
		"../../resources/textures/sincity_dn.tga",
		
		"../../resources/textures/sincity_rt.tga",
		"../../resources/textures/sincity_lf.tga"
	);		

	Shader pointShader = loadShader(
		"../../resources/shaders/point.vert",
		"../../resources/shaders/point.frag");

	Shader cubeShader = loadShader(
		"../../resources/shaders/cubemap.vert", 
		"../../resources/shaders/cubemap.frag");

	Shader reflectShader = loadShader(
		"../../resources/shaders/reflectSky.vert",
		"../../resources/shaders/reflectSky.frag");

	Shader refractShader = loadShader(
		"../../resources/shaders/refractSky.vert",
		"../../resources/shaders/refractSky.frag");

	Shader tfShader = loadUpdateShader("../../resources/shaders/update.vert");	
	
	// Reflection test
	Geometry ss = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;
	//////////////////////////
	// Camera Data
	Camera cam;
	//cam.view = glm::lookAt(
	//	glm::vec3(1, 1, 0),		// eye
	//	glm::vec3(0, 1, 0),		// center
	//	glm::vec3(0, 1, 0));	// up
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 100.f);

	//////////////////////////
	// Light
	StandardLight l;
	l.dir = glm::normalize(glm::vec3(.2, -1, -1));
	l.color = glm::vec4(1.0, .5, 1.0, 1);
	l.intensity = 4.0;
	l.ambient = glm::vec4(.2, .5, .1, 1);
	l.type = 0;

	Framebuffer screen = { 0, 1280, 720 };	

	
	glm::mat4 cube_model;

	
	ParticleVertex pVerts =
	{
		{ -.5f,-.5f, 0, 1 },{ .1,.1,0 },{ 1,0,0,1 }
	};

	

	const int MaxParticles = 1000000;
	ParticleVertex *ParticlesContainer = new ParticleVertex[MaxParticles];
	for (int i = 0; i < MaxParticles; ++i) 
	{
		double x = r2(-1.0f, 1.0f);
		double y = r2(-1.0f, 1.0f);
		double z = r2(-1.0f, 1.0f);

		double vX = r2(-0.5f, 0.5f);
		double vY = r2(-0.5f, 0.5f);
		double vZ = r2(-0.5f, 0.5f);
		ParticlesContainer[i] = {
			{ x,y,z, 1 },{ x,y,z },{x,y,z,1 }
		};

		//ParticlesContainer[i] = {
		//	{ 0,0,0,1 },{ 0,0,0 },{ x,y,z,1 }
		//};
	}

	ParticleBuffer pb = makeParticleBuffer(ParticlesContainer, MaxParticles);
	while (context.step())
	{
		float time = (float)context.getTime();
		int loc = 0, slot = 0;

		cube_model = glm::translate(glm::vec3(10, 1, 0)) * glm::scale(glm::vec3(2, 2, 2));
		model = glm::scale(glm::vec3(20, 20, 20));
		
		ss_model = glm::translate(glm::vec3(0, -2, -4)) * glm::rotate(time * 5, glm::vec3(.7, 1, .3));

		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);



		// SKYBOX
		if (context.getKey(' '))
		{
			model = glm::rotate(time / 20, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(10, 10, 10));

			loc = 0, slot = 0;
			setUniforms(cubeShader, loc, slot, cam, model, cityMap);
			s0_draw(screen, cubeShader, cubeGeo);
		}
		
		// PARTICLES
		loc = 0, slot = 0;	
		setUniforms(tfShader, loc, slot, time);
		tf0_update(tfShader, pb, 0);
		std::swap(pb.vbo[0], pb.vbo[1]);

		loc = 0, slot = 0;
		setUniforms(pointShader, loc, slot, cam, model, coolcat, time);
		tf0_draw(screen, pointShader, pb);

		// SPINNING REFRACTING CUBE
		loc = 0, slot = 0;
		setUniforms(refractShader, loc, slot, cam, ss_model, cityMap, time);
		s0_draw(screen, refractShader, cubeGeo);
		
	}


	context.exit();
}
