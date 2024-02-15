#include "scene_3d_test.h"

#include <glm/glm.hpp>

#include <core/input.h>
#include <core/asset.h>

#include <system/render_system.h>

#include <render/device.h>
#include <render/Shader.h>


float cube_vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};


struct SceneData {
	glm::mat4 mvp;
	glm::mat4 model;
};

static gpu::Buffer* vb;
static gpu::Buffer* ib;


static ConstantBufferHandle* cbh;

static Shader* shd;

static RenderSystem rs;

static Vector<String> debug_msgs;

static SceneData sd;

static float rotation;

void Test3DScene::init()
{
	cbh = new ConstantBufferHandle();

	cbh->name = "SceneData";

	
	target = gpu::device->create_target({
		.w = 1280,
		.h = 720
	});

	vb = gpu::device->create_buffer({
		.layout = { {3 , GL_FLOAT}, {3, GL_FLOAT }, {2, GL_FLOAT} },
		.bindFlags = gpu::BindFlags::BIND_VERTEX_BUFFER,
		.usageFlags = gpu::UsageFlags::STATIC_DRAW,
		.size = sizeof(cube_vertices),
		.data = cube_vertices,
	});
	
	cbh->buf = gpu::device->create_buffer({
		.bindFlags = gpu::BindFlags::BIND_CONSTANT_BUFFER,
		.usageFlags = gpu::UsageFlags::STATIC_DRAW,
		.size = sizeof(sd),
		.data = &sd,
	});

	shd = Asset::load_shader("3d");
}

void Test3DScene::destroy()
{

}

void Test3DScene::update()
{
	Scene::update();

	rotation += 0.05;

	sd.mvp = glm::perspectiveFovLH<float>(45.0f, 1280.0f, 720.0f, 0.1f, 10.0f);
	sd.mvp *= glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 2)), rotation, glm::vec3(1, 1, 0));


	gpu::device->update_buffer(cbh->buf, &sd, sizeof(sd));

	DrawCall dc;
	dc.buffer = vb;
	dc.uniform = cbh;
	dc.vertices_count = 36;
	dc.shader = shd;

	rs.submit_drawcall(dc);

	//debug_msgs.push_back("Drawcalls: ");
}

void Test3DScene::render()
{
	ren->set_target(target);
	ren->clear(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	//int y = 0;
	//for (auto s : debug_msgs)
	//{
	//	ren->draw_text(s, Renderer::DefaultFont, Vec2(10, 10 + y));
	//	y += 20;
	//}

	//debug_msgs.clear();

	//Scene::render();

	rs.work();

	ren->set_target(Renderer::Viewport);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));


	ren->draw_target(target);
}

