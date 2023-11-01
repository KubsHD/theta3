#include "scene_light_test.h"

#include <glm/glm.hpp>
#include <core/input.h>
#include <render/device.h>
#include <core/asset.h>
#include <core/game.h>

static int x = 300;

void LightTestScene::init()
{
	target = gpu::device->create_target({ 1280, 720, TargetScalingType::Nearest});
	lit_shader = Asset::load_shader("lit");
	test = Asset::load_texture("coin.png");
}

void LightTestScene::destroy()
{

}

void LightTestScene::update()
{
	Scene::update();

	lit_shader->set_uniform_vec2("u_lightPos", Vec2(x, 200.0f));

	x += 1;
	if (x > 400)
		x = 150;
}

void LightTestScene::render()
{
	ren->set_target(target);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_tex_s(test, Vec2(250.0f, 150.0f), Vec2(100.0f, 100.0f), lit_shader);
	//ren->draw_tex(test, Vec2(x, 200.0f));

	Scene::render();


	ren->set_target(Renderer::Viewport);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_target(target);
}

