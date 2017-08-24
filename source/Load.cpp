#include <string>
#include <fstream>
#include <iostream>

#include "graphics\Load.h"
#include "graphics\RenderObjects.h"

#include "OBJ\tiny_obj_loader.h"
#include "graphics\Vertex.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"


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

Geometry loadGeometry(const char * path)
{
	Geometry retval = { 0,0,0,0 };
	tinyobj::attrib_t attrib;					// vertex data
	std::vector<tinyobj::shape_t> shapes;		// tri data, indices
	std::vector<tinyobj::material_t> materials;	// texture paths
	std::string err;							// error string

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	size_t vsize = attrib.vertices.size() / 3;
	Vertex *verts = new Vertex[vsize];

	for (size_t i = 0; i < vsize; ++i) 
	{
		const float *p = &attrib.vertices[i * 3];
		verts[i].position = {p[0], p[1], p[2], 1};
	}

	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];

	for (size_t i = 0; i < isize; ++i)
	{
		indices[i] = shapes[0].mesh.indices[i].vertex_index;
	}	

	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;

	return retval;
}
