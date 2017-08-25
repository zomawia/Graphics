#pragma once

#include "glm\glm.hpp"
#include "glm\ext.hpp"

#include "RenderObjects.h"

struct Transform
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat3 rotation; // best to use an interface or helper function

	Transform *parent = nullptr;

	glm::mat4 getLocal() const; // evaluate local matrix: (T*R*S)
	glm::mat4 getGlobal() const; // evaluate global: parent.global * local

								 // helpers for setting a meaningful rotation:
	void axisAngle(float angle, const glm::vec3 &axis = { 0,1,0 });
	void lookAt(const glm::vec3 &target, const glm::vec3 &up = { 0,1,0 });
};

struct Camera
{
	Transform transform;

	float fov = 45.f, aspect = 8.f / 6.f, near = 0.01f, far = 100.0f;

	glm::mat4 getProjection() const;
	glm::mat4 getView() const;
};

struct Mesh
{
	Transform transform;

	Geometry geometry;
};

struct FlyCam
{
	Camera camera;

	float speed;
	// add any members needed to keep track of input


	// Check input and modify camera.transform accordingly
	void update(float dt);
};

struct OrbitCam
{
	Camera camera;

	float speed;
	// add any members needed to keep track of input
	glm::vec3 target;

	// Check input and modify camera.transform accordingly
	void update(float dt);
};