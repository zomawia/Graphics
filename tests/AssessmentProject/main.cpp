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
	
	Geometry cubeGeo = loadGeometry("../../resources/textures/cube.obj");

	CubeTexture cubeTex = loadCubeMap(
		"../../resources/textures/stormydays_rt.tga", 
		"../../resources/textures/stormydays_lf.tga",
		"../../resources/textures/stormydays_up.tga",
		"../../resources/textures/stormydays_dn.tga",
		"../../resources/textures/stormydays_bk.tga",
		"../../resources/textures/stormydays_ft.tga");

	Shader cubeShader = loadShader(
		"../../resources/shaders/direct.vert", 
		"../../resources/shaders/cubemap.frag");

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



	}


	context.exit();
}
