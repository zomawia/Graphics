#include "..\include\graphics\RenderObjects.h"
#include "glinc.h"
#include "graphics\Vertex.h"

#ifdef _DEBUG
#include <iostream>
#endif

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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

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
