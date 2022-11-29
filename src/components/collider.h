#pragma once

#include <core/types.h>
#include <core/ecs.h>

#include <functional>
#include <render/Renderer.h>


class Collider : public Component {

public:
	Collider() = default;
	Collider(Vec2 size, Vec2 offset) : size(size), offset(offset) {};

	Vec2 size;
	Vec2 offset;
	Vec2 position;
	
	std::function<void(Entity* other)> on_collision_enter;
	std::function<void(Entity* other)> on_collision_leave;

	void update() override
	{
		position = entity->position;
	}

	void render(Renderer* ren) override
	{
		ren->draw_box(entity->position, size, Vec3(0.1f, 0.1f, 1.0f));
	}

};