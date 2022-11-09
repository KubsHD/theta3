#pragma once

#include <core/types.h>
#include <core/ecs.h>

class Collider : public Component {
public:
	Collider() {};

	void update() override
	{
	}


	void render(Renderer* ren) override
	{
		ren->draw_box(entity->position, entity->size, Vec3(0.1f, 0.1f, 1.0f));
	}

};