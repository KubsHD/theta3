#pragma once

#include <core/types.h>
#include <core/ecs.h>

#include <functional>
#include <render/Renderer.h>

// Add collision types here
enum class CollisionTag {
	Solid = 0,
	Enemy = 1,
	Bullet = 2,
	Pickup = 3,
	Player = 4,
};

class Collider : public Component {

public:
	Collider() = default;
	Collider(Vec2 size, Vec2 offset) : size(size), offset(offset) {};

	Vec2 size;
	Vec2 offset;
	Vec2 position;

	CollisionTag tag;
	
	std::function<void(Entity* other)> on_collision_enter;
	std::function<void(Entity* other)> on_collision_leave;

	bool check_sphere(Vec2 point, float radius, CollisionTag tagToQueryFor)
	{
		return this->entity->world->collision_query_sphere(this, point, radius, tagToQueryFor);
	}

	void update() override
	{
		position = entity->position;
	}

	void render(Renderer* ren) override
	{
		ren->draw_box(entity->position, size, Vec3(0.1f, 0.1f, 1.0f));
	}

};