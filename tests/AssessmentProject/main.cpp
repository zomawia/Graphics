///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//	Zomawia Sailo//		
//		Graphics Library Assessment Project
//
//	Planned library extensions
//	1. Cube-mapping support
//		- skyboxes
//		- reflections
//	2. Transform feedback
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#include "graphics\GameObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include "graphics\Context.h"
#include "graphics\draw.h"

void main()
{
	Context context;
	context.init(1280, 720);
	
	Geometry cubeGeo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 model;

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

		

	Shader cubeShader = loadShader(
		"../../resources/shaders/cubemap.vert", 
		"../../resources/shaders/cubemap.frag");

	//////////////////////////
	// Camera Data
	Camera cam;
	cam.view =
	
		glm::lookAt(
		glm::vec3(1, 1, 1),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0));
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

	while (context.step())
	{
		float time = context.getTime();
		int loc = 0, slot = 0;

		model = glm::rotate(time/60, glm::vec3(0,1,0)) * glm::scale(glm::vec3(10, 10, 10));

		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		setUniforms(cubeShader, loc, slot, cam, model, cityMap);
		s0_draw(screen, cubeShader, cubeGeo);
	}


	context.exit();
}
