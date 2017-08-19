#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Context.h"

int main() {
	Context context;
	context.init();

	const double PI = 3.14159265359;

	///////////////////////////////
	Vertex verts[9] =
	{
		{ { -.75f,-.5f, 0, 1 },{ 1,0,0,1 },{ .0001,glm::sin(PI)/360 } },
		{ { -.25f, .5f, 0, 1 },{ 0,1,0,1 },{ .1,.5 } },
		{ { 1,  .15f, 0, 1 },{ 1,0,1,1 },{ glm::sin(PI),20 } },
		{ { .75f,-.35f, 0, 1 } ,{ 0,1,1,1 },{ 5,2/glm::cos(PI) } },
		{ { -.75f, .7f, 0, 1 },{ 1,0,0,1 },{ glm::sin(PI),200 } },
		{ { -.55f, .25f, 0, 1 },{ 0,1,0,1 },{ .00011,.5 } }		
	};

	unsigned idxs[18] = { 0,1,2,4,3,0,5,4,0,6,5,0,7,6,0,8,7,0};	

	Geometry g = makeGeometry(verts, 6, idxs, 18);

	double xPos = 0, yPos = 0;

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 texPos;\n"

		//"layout(location = 2) uniform float x;\n"
		//"layout(location = 3) uniform float y;\n"		

		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"out vec2 UVPos;\n"

		"void main ()\n"
		"{\n"
		"UVPos = texPos;\n"
		"gl_Position = position;\n"
		"gl_Position.y -= sin(time+position.x)/20.0;\n"
		"gl_Position.x += sin(time+position.y)/50.0;\n"
		//"gl_Position.x += x;\n"
		//"gl_Position.y += y;\n"
		"vColor = color;\n"
		"vUV -= 2 * sin(texPos + 3) ;\n"		
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"

		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int tog;\n"
		"layout(location = 2) uniform sampler2D map;\n"
		"layout(location = 3) uniform sampler2D mask;\n"

		"in vec4 vColor;\n"
		"in vec2 vUV;\n"
		"in vec2 UVPos;\n"

		"void main ()\n"
		"{\n"
		"vec2 poop = UVPos;\n"
		"poop.x += 3 * sin(.5*time+gl_FragCoord.x)/2;\n"
		"poop.y += .2 * sin(.25*time+gl_FragCoord.y)/2;\n"
		"outColor = texture(map, sin(poop*time)) * texture(mask,vUV).r;\n"
		//"outColor.x += sin(time);\n"
		//"outColor.y += sin(time/4);\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);
	
	Framebuffer f = { 0, 800, 800 };

	unsigned char pixels[] = {	255,0,255,0,
								255,0,255,0, 
								0,255,0,255,
								255,0,255,0	};
	Texture t_mask = makeTexture(4, 4, 1, pixels);
	Texture t_magyel = makeTexture(4, 1, 3, pixels);

	//////////////////////////////////////
	
	glm::vec2 pos = { 0,0 };
	float speed = 1.2f;
	float prevTime = 0;
	while (context.step()) {
		float ct = context.getTime();
		float dt = ct - prevTime;
		prevTime = ct;

		glm::vec2 vel = { 0,0 };

		//context.getMousePosition(xPos,yPos);		
		//vel.y += context.getKey('W');
		//vel.y -= context.getKey('S');
		//vel.x -= context.getKey('A');
		//vel.x += context.getKey('D');

		if (glm::length(vel) > 0) {			
			pos += glm::normalize(vel) * dt * speed;
		}		

		clearFramebuffer(f);
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, (int)context.getKey(' '));
		//setUniform(s, 2, pos.x);
		//setUniform(s, 3, pos.y);
		
		setUniform(s, 2, t_magyel, 0);
		setUniform(s, 3, t_mask, 1);

		s0_draw(f, s, g);		
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);
	freeTexture(t_mask);
	context.exit();
	return 0;
}