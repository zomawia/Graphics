#define GLM_FORCE_SWIZZLE

#include "..\include\graphics\RenderObjects.h"
#include "glinc.h"
#include "graphics\Vertex.h"

#include "glm\ext.hpp"



#ifdef _DEBUG
#include <iostream>
#endif

glm::vec4 calcTangent(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
	// Calculate the left and right edge of the triangle
	glm::vec4 p1 = v1.position - v0.position;
	glm::vec4 p2 = v2.position - v0.position;

	// calculate the left and right edge of the triangle's UVs
	glm::vec2 t1 = v1.texCoord - v0.texCoord;
	glm::vec2 t2 = v2.texCoord - v0.texCoord;

	// Rotate the position edge to line up with the texture edge and normalize
	return glm::normalize((p1*t2.y - p2*t1.y) / (t1.x*t2.y - t1.y*t2.x));
}

void solveTangents(Vertex * v, size_t vsize, const unsigned * idxs, size_t isize)
{
	// for each triangle
	for (int i = 0; i < isize; i += 3)
	{
		glm::vec4 T = calcTangent(v[idxs[i + 0]], v[idxs[i + 1]], v[idxs[i + 2]]);

		// Average tangents out for each vertex
		for (int j = 0; j < 3; ++j)
			v[idxs[i + j]].tangent = glm::normalize(T + v[idxs[i + j]].tangent);
	}	

	// Evaluate bitangent afterward
	for (int i = 0; i < vsize; ++i)
		v[i].bitangent = glm::vec4(glm::cross(v[i].normal.xyz(), v[i].tangent.xyz()), 0);
}

Geometry makeGeometry(const Vertex * vertices, size_t vsize, const unsigned * indices, size_t isize)
{	
	Geometry retval = { 0,0,0,isize };

	// declare our OpenGL objects and acquire handles
	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.handle); //stores information on how memory is laid out

	// scope our handles
	// VAO must be bound first so that openGL will bind the VBO and IBO to it.
	glBindVertexArray(retval.handle);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);

	// initialize the buffers with our own data.
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(unsigned), indices, GL_STATIC_DRAW);	

	// activate an attribute and then provide details about that attribute
	//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);
	//tex coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	//normals
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)40);
	//tangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56);
	//bitangent
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)72);

	//unbind the VAO first, otherwise the VAO will dissociate from the VBO and IBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

void freeGeometry(Geometry & g)
{
	glDeleteBuffers(1, &g.vbo);
	glDeleteBuffers(1, &g.ibo);
	glDeleteVertexArrays(1, &g.handle);
	g = { 0,0,0,0 };

}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader retval = { 0 };

	// use local variables to track the handles when we create them
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	// load up the source code and compile
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	
	glCompileShader(vs);
		#ifdef _DEBUG
			GLint successVS = GL_FALSE;
			glGetShaderiv(vs, GL_COMPILE_STATUS, &successVS);
			if (successVS == GL_FALSE)
			{
				int length = 0;
				glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
				char *log = new char[length];
				glGetShaderInfoLog(vs, length, 0, log);
				std::cerr << log << std::endl;
				delete[] log;
			}
		#endif _DEBUG

	glCompileShader(fs);
		#ifdef _DEBUG
			GLint successFS = GL_FALSE;
			glGetShaderiv(fs, GL_COMPILE_STATUS, &successFS);
			if (successFS == GL_FALSE)
			{
				int length = 0;
				glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
				char *log = new char[length];
				glGetShaderInfoLog(fs, length, 0, log);
				std::cerr << log << std::endl;
				delete[] log;
			}
		#endif _DEBUG


	// attach each shader to the shader program and link.
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);

		#ifdef _DEBUG
			GLint success = GL_FALSE;
			glGetProgramiv(retval.handle, GL_LINK_STATUS, &success);
			if (success == GL_FALSE)
			{
				int length = 0;
				glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &length);
				char *log = new char[length];
				glGetProgramInfoLog(retval.handle, length, 0, log);
				std::cerr << log << std::endl;
				delete[] log;			}
		#endif _DEBUG

	// Before we finish we can now delete the individual shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &s)
{
	glDeleteProgram(s.handle);
	s = { 0 };
}

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char * pixels)
{
	Texture retval = { 0 };
	
	unsigned f = 0;
	
	switch (c) {
	case 1: f = GL_RED; break;
	case 2: f = GL_RG; break;
	case 3: f = GL_RGB; break;
	case 4: f = GL_RGBA; break;
	}	

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, f, 
		GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);	

	return retval;
}

void freeTexture(Texture & t)
{
	glDeleteTextures(1, &t.handle);
	t = {0};
}
