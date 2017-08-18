#pragma once
#include "graphics\RenderObjects.h"


Geometry makeNGon(size_t sides, float r);

Geometry makeCheckerboard(int dim, float size);

Geometry makeCheckerboard(int rows, int cols, float width, float height);