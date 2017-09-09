#include "graphics\GameObjects.h"
#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Load.h"

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Camera & val)
{
	t_setUniform(s, loc_io, tex_io, val.proj); // 0
	t_setUniform(s, loc_io, tex_io, val.view); // 1
}

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const SpecGloss & val)
{
	t_setUniform(s, loc_io, tex_io, val.model);	   // 0 matrix

	t_setUniform(s, loc_io, tex_io, val.diffuse);  // 1 texture
	t_setUniform(s, loc_io, tex_io, val.specular); // 2 texture
	t_setUniform(s, loc_io, tex_io, val.normal);   // 3 texture
	t_setUniform(s, loc_io, tex_io, val.gloss);    // 4 float
}

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const DirectionalLight & val)
{
	t_setUniform(s, loc_io, tex_io, val.getProj());	//0
	t_setUniform(s, loc_io, tex_io, val.getView());	//1
	t_setUniform(s, loc_io, tex_io, val.color);		//2
	t_setUniform(s, loc_io, tex_io, val.intensity);	//3
}

SimplePresetScene::SimplePresetScene()
{
	// floor
	Vertex vquad[] = { { { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	go[0].geo = makeGeometry(vquad, 4, quadidx, 6);
	go[0].model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));
	go[0].diffuse = loadTexture("../../resources/textures/four_diffuse.tga");
	go[0].specular = loadTexture("../../resources/textures/four_specular.tga");
	go[0].normal = loadTexture("../../resources/textures/four_normal.tga");
	go[0].gloss = 4;

	// Soulspear
	go[1].geo = loadGeometry("../../resources/models/soulspear.obj");
	go[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	go[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	go[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	go[1].gloss = 4;

	// Earth
	go[2].geo = loadGeometry("../../resources/models/sphere.obj");
	go[2].diffuse = loadTexture("../../resources/textures/earth_diffuse.jpg");
	go[2].specular = loadTexture("../../resources/textures/earth_specular.jpg");
	go[2].normal = loadTexture("../../resources/textures/earth_normal.jpg");
	go[2].model = glm::scale(glm::vec3(2, 2, 2)) * glm::translate(glm::vec3(2, 1, -1));
	go[2].gloss = 4;

	// Camera
	cam.view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);

	// Light 1
	dl[0].target = glm::vec3(0, 0, 0);
	dl[0].color = glm::vec4(.9, .5, .1, 1);
	dl[0].direction = glm::normalize(glm::vec3(.8, -1, -1));
	dl[0].intensity = 1.4;

	// Light 2
	dl[1].target = glm::vec3(0, 0, 0);
	dl[1].color = glm::vec4(.1, .5, .9, 1);
	dl[1].direction = glm::normalize(glm::vec3(.1, -.2, -4));
	dl[1].intensity = .8;
}