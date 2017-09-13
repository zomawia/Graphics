#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "glinc.h"

void setFlags(int flags)
{
	// depth testing
	if (flags & RenderFlag::DEPTH) 
		glEnable(GL_DEPTH_TEST);
	else 
		glDisable(GL_DEPTH_TEST);

	if (flags &RenderFlag::ADDITIVE) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
	}	

	else glDisable(GL_BLEND);
}

void s0_draw(const Framebuffer & f, const Shader & s, const Geometry & g)
{
	// First we need to scope all of the OpenGL objects that we’ll be using.
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	// The Viewport Rectangle could be used for something like split screen or atlases. 
	// The first two variables are the starting pixel < iX, iY > 
	// and the last two are the dimensions of the space we want to draw to.
	glViewport(0, 0, f.width, f.height);

	// Drawing is performed using the index buffer. 
	// We provide how polygons will be formed and how many.


	//glDrawElements(GL_TRIANGLE_FAN, g.size, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}

void clearFramebuffer(const Framebuffer & fb, bool color, bool depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
	glClear(GL_COLOR_BUFFER_BIT * color | GL_DEPTH_BUFFER_BIT * depth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setUniform(const Shader &s, int location, float value)
{
	glProgramUniform1f(s.handle, location, value);
}

void setUniform(const Shader & s, int location, int value)
{	
	
	if (value == 1) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	}
	else {
		glProgramUniform1i(s.handle, location, value);
		glDisable(GL_BLEND);
	}
}

//void setUniform(const Shader & s, int location, float x, float y)
//{
//	glProgramUniform1f(s.handle, location, x);
//	glProgramUniform1f(s.handle, location+1, y);
//}

void setUniform(const Shader & s, int location, const Texture & value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle, location, slot);	
}

namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val) {
		glProgramUniform1f(s.handle, loc_io++, val);
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val) {
		glProgramUniform1i(s.handle, loc_io++, val);
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val) {
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_2D, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const CubeTexture & val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_CUBE_MAP, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}

	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val) {
		glProgramUniformMatrix4fv(s.handle, loc_io++, 1, 0, glm::value_ptr(val));
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val) {
		glProgramUniform4fv(s.handle, loc_io++, 1, glm::value_ptr(val));
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val) {
		glProgramUniform3fv(s.handle, loc_io++, 1, glm::value_ptr(val));
		
	}
}


