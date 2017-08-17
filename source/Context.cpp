#include "../include/graphics/Context.h"
#include "glinc.h"

#ifdef _DEBUG
#include <iostream>
void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message, const void *userParam) {
	std::cerr << message << std::endl;
}
#endif


bool Context::getKey(int key){			

	return glfwGetKey(handle, key);
}

bool Context::getMouseButton(int button)
{
	return glfwGetMouseButton(handle, button);
}

void Context::getMousePosition(double & x_out, double & y_out)
{
	glfwGetCursorPos(handle, &x_out, &y_out);
}

double Context::getTime()
{
	return glfwGetTime();
}

int Context::getJoystickPresent(int joy)
{
	return glfwJoystickPresent(joy);
}

void Context::setTime(double time)
{
	glfwSetTime(time);
}

bool Context::init(size_t w, size_t h, const char *title) {
	glfwInit();

	handle = glfwCreateWindow(w, h, title, nullptr, nullptr);
	glfwMakeContextCurrent(handle);

	glewExperimental = true;
	glewInit();
	
#ifdef _DEBUG

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);

#endif

	return true;
}

bool Context::step() {
	glfwPollEvents();
	glfwSwapBuffers(handle);
	return !glfwWindowShouldClose(handle);	
}

bool Context::exit() {
	glfwTerminate();
	handle = nullptr;
	return true;
}

