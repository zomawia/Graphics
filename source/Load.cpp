#include <string>
#include <fstream>
#include <iostream>
#include <random>

#include "glm\ext.hpp"

#include "graphics\Load.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"



glm::vec4 randColor()
{
	return {rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1};
}



std::string readFile(const char *filePath) {
	//http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/

	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

Shader loadShader(const char *vert_path, const char *frag_path)
{	
	std::string vertSTR = readFile(vert_path);
	std::string fragSTR = readFile(frag_path);

	const char* vertSRC = vertSTR.c_str();
	const char* fragSRC = fragSTR.c_str();
	
	Shader retval = { 0 };

	retval = makeShader(vertSRC, fragSRC);

	return retval;
}

Geometry loadGeometry(const char *path)
{
	Geometry retval = { 0,0,0,0 };
	tinyobj::attrib_t attrib;				// Vertex Data is stored.
	std::vector<tinyobj::shape_t> shapes;	// Triangular data, indices.
	std::vector<tinyobj::material_t> materials;
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	/////////////////////////////////////////////////////////////////
	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];

	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (int i = 0; i < isize; ++i)
	{
		indices[i] = i;

		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ni = shapes[0].mesh.indices[i].normal_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index;

		const float *p = &attrib.vertices[pi * 3];  // 3x
		const float *n = &attrib.normals[ni * 3];   // 3x
		const float *t = &attrib.texcoords[ti * 2]; // 2x

		verts[i].position = { p[0],p[1],p[2],1 };
		verts[i].texCoord = { t[0],t[1] };
		verts[i].normal = { n[0],n[1],n[2],0 };
		verts[i].color = randColor();
	}
	///////////////////////////////////////////////////////////////////

	solveTangents(verts, vsize, indices, isize);

	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;
	return retval;
}

Texture loadTexture(const char * path)
{
	Texture retval = { 0 };

	int w, h, c;
	unsigned char *pixels;

	stbi_set_flip_vertically_on_load(true);

	pixels = stbi_load(path, &w, &h, &c, STBI_default);

	retval = makeTexture(w, h, c, pixels);
	stbi_image_free(pixels);

	return retval;
}

CubeTexture loadCubeMap(const char * path_Xpos, const char * path_Xneg, const char * path_Ypos, const char * path_Yneg, const char * path_Zpos, const char * path_Zneg)
{
	CubeTexture retval = { 0 };

	int w, h, c;
	unsigned char **pixels = new unsigned char*[6];

	stbi_set_flip_vertically_on_load(true);

	pixels[0] = stbi_load(path_Xpos, &w, &h, &c, STBI_default);
	pixels[1] = stbi_load(path_Xneg, &w, &h, &c, STBI_default);
	
	pixels[2] = stbi_load(path_Ypos, &w, &h, &c, STBI_default);
	pixels[3] = stbi_load(path_Yneg, &w, &h, &c, STBI_default);

	pixels[4] = stbi_load(path_Zpos, &w, &h, &c, STBI_default);
	pixels[5] = stbi_load(path_Zneg, &w, &h, &c, STBI_default);

	retval = makeCubeMap(w, h, c, pixels);
	stbi_image_free(pixels);

	return retval;
}

CubeTexture loadCubeMap(std::vector<std::string> faces)
{
	CubeTexture retval = { 0 };

	//todo

	return retval;
}




