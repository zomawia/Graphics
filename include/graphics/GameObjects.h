#pragma once

#include "glm\glm.hpp"
#include "glm\ext.hpp"

#include "RenderObjects.h"

struct Camera
{
	glm::mat4 proj;
	glm::mat4 view;
};

struct SpecGloss 
{
	Geometry geo;

	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;
};

struct StandardLight
{
	glm::vec3 dir;
	glm::vec3 color;	
	float intensity;
	glm::vec4 ambient;
	int type;
};

// 0: proj, 1: view, 2: color, 3: intensity
struct DirectionalLight
{

	glm::vec3 target; // for shadow mapping
	float range;	  // for shadow mapping

	glm::vec3 direction;

	// 0
	glm::mat4 getProj() const
	{
		return glm::ortho<float>(-range, range, -range, range, -range, range);
	}

	// 1
	glm::mat4 getView() const
	{
		return glm::lookAt(-direction + target, target, glm::vec3(0, 1, 0));
	}

	glm::vec4 color; // 2
	float intensity; // 3
};


struct SimplePresetScene
{
	Camera cam;
	SpecGloss go[3];
	DirectionalLight dl[2];

	SimplePresetScene();
};

namespace __internal
{	
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Camera &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const SpecGloss &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const DirectionalLight &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const CubeTexture &val);
}