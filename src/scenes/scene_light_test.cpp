#include "scene_light_test.h"

#include <glm/glm.hpp>
#include <core/input.h>
#include <render/device.h>

void LightTestScene::init()
{
	target = gpu::device->create_target({ 1280, 720 });
}

void LightTestScene::destroy()
{

}

void LightTestScene::update()
{
	Scene::update();

}

void LightTestScene::render()
{
	ren->set_target(target);
	ren->clear(Vec3(3.0f, 0.0f, 0.0f));

	Scene::render();

	ren->set_target(Renderer::Viewport);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_target(target);
}

