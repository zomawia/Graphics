#pragma once

#include "RenderObjects.h"

Texture loadTexture(const char *path);

Shader loadShader(const char *vert_path, const char *frag_path);

Geometry loadGeometry(const char *path);

