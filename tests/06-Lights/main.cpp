#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"

int main()
{
	Context context;
	context.init(800, 600);

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Shader lambert = loadShader("../../resources/shaders/lambert.vert",
		"../../resources/shaders/lambert.frag");
	
	Framebuffer screen = { 0,800,600 };

	while (context.step())
	{
		float time = context.getTime();

		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
		glm::mat4 go_model = glm::rotate(time, glm::vec3(0,1,0));
		glm::mat4 go_model1 = glm::translate(glm::vec3(-1.75,0, 0)) * go_model;
		glm::mat4 go_model2 = glm::translate(glm::vec3(1.75,0, 0)) * go_model;

		glm::vec3 dl_dir = glm::normalize(glm::vec3(1, -1, 1));
		glm::vec4 dl_col = glm::vec4(.7f, .6f, .2f, 1.f);

		clearFramebuffer(screen);
		setFlags(RenderFlag::DEPTH);

		int loc = 0, tslot = 0;

		setUniforms(lambert, loc, tslot, cam_proj, cam_view, go_model, ss_diffuse,
			dl_dir, dl_col);

		s0_draw(screen, lambert, ss_geo);

		loc = 0, tslot = 0;
		setUniforms(lambert, loc, tslot, cam_proj, cam_view, go_model1, ss_diffuse,
			dl_dir, dl_col);

		s0_draw(screen, lambert, ss_geo);

		loc = 0, tslot = 0;
		setUniforms(lambert, loc, tslot, cam_proj, cam_view, go_model2, ss_diffuse,
			dl_dir, dl_col);

		s0_draw(screen, lambert, ss_geo);


	}

	context.exit();
	return 0;

}
