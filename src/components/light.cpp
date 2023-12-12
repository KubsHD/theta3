#include "light.h"

#include <render/Renderer.h>
#include <render/light_system.h>

void Light::init()
{
	switch (Type) {
		case LightType::Spot:
			this->entity->world->ren->Light->add_spot_light();
			break;
		case LightType::Point:
			this->entity->world->ren->Light->add_point_light(this);
			break;
	}
}

void Light::update()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Light::render(Renderer* ren)
{
	throw std::logic_error("The method or operation is not implemented.");
}

