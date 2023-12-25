#include "flashlight.h"
#include "light.h"
#include <render/Renderer.h>
#include <render/light_system.h>
#include <core/input.h>
#include <core/log.h>
#include <core/game.h>

void Flashlight::init()
{
	m_lightRef = this->entity->add(Light(this->entity->world->ren->light, LightType::Spot));
	m_lightRef->spot.color = Vec3(0.4, 0.3, 0.2);
	m_lightRef->spot.angle = 0;
	m_lightRef->spot.radius = 200;
	m_lightRef->spot.width = 75;
}

void Flashlight::update()
{
	//m_lightRef->spot.angle += 0.01 * Game::get_delta();

	auto destination = Input::get_mouse_pos();


	auto viewportSize = Input::get_viewport_size();

	auto delta_x = destination.x - viewportSize.x / 2;
	auto delta_y = destination.y - viewportSize.y / 2;

	m_lightRef->spot.angle = glm::degrees(atan2(delta_y, delta_x)) + 180;


	log_info("fl: %f  %f    ang: %f\n", Input::get_mouse_pos().y, Input::get_mouse_pos().x, m_lightRef->spot.angle);

}

void Flashlight::render(Renderer* ren)
{
}

void Flashlight::destroy()
{
}

