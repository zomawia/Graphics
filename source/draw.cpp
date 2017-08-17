#include "graphics\draw.h"
#include "glinc.h"

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

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}
