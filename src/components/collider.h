#pragma once

#include <core/types.h>
#include <core/ecs.h>

class Collider : public Component {
	Vec2 m_size;
	Vec2 m_offset;

public:
	Collider() = default;
	Collider(Vec2 size, Vec2 offset) : m_size(size), m_offset(offset) {};

	std::function<void(Entity* other)> on_collision;

	void update() override
	{
	}


	void render(Renderer* ren) override
	{
		ren->draw_box(entity->position, entity->size, Vec3(0.1f, 0.1f, 1.0f));
	}

};