#include "flashlight.h"
#include "light.h"
#include <render/Renderer.h>
#include <render/light_system.h>
#include <core/input.h>
#include <core/log.h>
#include <core/game.h>
#include <glm/glm.hpp>

void Flashlight::init()
{
	m_lightRef = this->entity->add(Light(this->entity->world->ren->light, LightType::Spot));
	m_lightRef->spot.color = Vec3(0.9, 0.9, 0.9);
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


	//log_info("fl: %f  %f    ang: %f\n", Input::get_mouse_pos().y, Input::get_mouse_pos().x, m_lightRef->spot.angle);

	float target_width = 75.0f;

	if (Input::mouse_held(1))
	{
		target_width = 45.0f;
		//this->entity->world->ren->get_camera()->zoom = 2.0f;
	}
	else {
		//this->entity->world->ren->get_camera()->zoom = 1.0f;
	}

	m_lightRef->spot.width = std::lerp(m_lightRef->spot.width, target_width, 0.1f);
}

void Flashlight::render(Renderer* ren)
{
}

void Flashlight::destroy()
{
}

