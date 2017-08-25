#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

enum RenderFlag { DEPTH = 1 };

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;

void setFlags(int flags);

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry&g);

void clearFramebuffer(const Framebuffer &fb, bool color = true, bool depth = true);

void setUniform(const Shader &s, int location, float value);

void setUniform(const Shader &s, int location, int value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);

// Called each time the bariadic unpacking recursion takes place
// based upon what informs are passed in, the correct function automatically
// be called. In dooing so, the appropriate programming function will also be called.
namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val);
}

// The recursive template function.
// U is a variadic template paramete. Each time the function gets called,
// the T parameter (val) will consume 1 element of the variadic
// So if there is recursion, the uniform will slowly be eaten by the T parameter.

template<typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io,
	const T &val, U &&... uniforms)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
	// The T parameter isn't a part of this call
	// It is instead is stealing a value from the uniform's variadic
	setUniforms(s, loc_io, tex_io, uniforms...);
}

// Base case
// last function that gets called. Since T is always eating values from U
// Eventually there will be no more U. To Ensure that we have a valid
// function we need to have a base case like so:
template<typename T>
void setUniforms(const Shader &s, int &loc_io, int &tex_io,	const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);	
}