#include "light.h"

#include <render/Renderer.h>
#include <render/light_system.h>

Light::Light(LightSystem* ls, LightType type)
{
	this->type = type;
	m_lsRef = ls;
}

Light::~Light()
{

}

void Light::init()
{
	switch (type) {
		case LightType::Spot:
			m_handle = this->entity->world->ren->light->add_spot_light();
			break;
		case LightType::Point:
			m_handle = this->entity->world->ren->light->add_point_light();
			break;
	}
}

void Light::update()
{
	point.pos = entity->position;
	spot.pos = entity->position;

	switch (type) {
		case LightType::Spot:
			this->entity->world->ren->light->update_spot_light(m_handle, spot);
			break;
		case LightType::Point:
			this->entity->world->ren->light->update_point_light(m_handle, point);
			break;
	}}

void Light::render(Renderer* ren)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void Light::destroy()
{
	switch (type) {
	case LightType::Spot:
		m_lsRef->remove_spot_light(m_handle);
		break;
	case LightType::Point:
		m_lsRef->remove_point_light(m_handle);
		break;
	}
}

