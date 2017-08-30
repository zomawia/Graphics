#pragma once

#include "glm\glm.hpp"

struct Vertex;

struct Geometry {
	unsigned handle, vbo, ibo, size;
};

void solveTangents(Vertex *v, size_t vsize, const unsigned *idxs, size_t isize);


Geometry makeGeometry(const Vertex *vertices, size_t vsize, 
	const unsigned *indices, size_t isize);

void freeGeometry(Geometry &g);

struct Shader {
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);
void freeShader(Shader &s);


struct Framebuffer {
	unsigned handle, width, height;
};

struct Texture {
	unsigned handle;
};

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);
void freeTexture(Texture &t);