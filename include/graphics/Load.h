#pragma once

#include "RenderObjects.h"

Texture loadTexture(const char *path);

Shader loadShader(const char *vert_path, const char *frag_path);

Geometry loadGeometry(const char *path);

CubeTexture loadCubeMap(const char *path_Xpos, const char *path_Xneg,
	const char *path_Ypos, const char *path_Yneg,
	const char *path_Zpos, const char *path_Zneg);

Shader loadUpdateShader(const char *vert_path);