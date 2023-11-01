/*****************************************************************//**
 * \file   collider.h
 * \brief  this component is responsible for collision in game
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>

#include <functional>
#include <render/Renderer.h>

/// <summary>
/// here are collision types
/// </summary>
enum class CollisionTag {
	Solid = 0,
	Enemy = 1,
	Bullet = 2,
	Pickup = 3,
	Player = 4,
	Gun = 5
};

/// <summary>
/// this class create collider
/// </summary>
class Collider : public Component {

public:
	Collider() = default;
	Collider(Vec2 size, Vec2 offset) : size(size), offset(offset) {};

	Vec2 size;
	Vec2 offset;
	Vec2 position;

	std::pair<Vec2, float> last_circle_query;

	CollisionTag tag;
	
	std::function<void(Entity* other)> on_collision_enter;
	std::function<void(Entity* other)> on_collision_leave;

	bool check_sphere(Vec2 point, float radius, CollisionTag tagToQueryFor)
	{
		last_circle_query.first = point;
		last_circle_query.second = radius;
		return this->entity->world->collision_query_sphere(this, point, radius, tagToQueryFor);
	}

	bool check_sphere(Vec2 point, float radius, CollisionTag tagToQueryFor, Entity& hit)
	{
		last_circle_query.first = point;
		last_circle_query.second = radius;
		return this->entity->world->collision_query_sphere_result(this, point, radius, tagToQueryFor, hit);
	}


	std::list<Collider*> check_sphere_list(Vec2 point, float radius, CollisionTag tagToQueryFor)
	{
		last_circle_query.first = point;
		last_circle_query.second = radius;
		return this->entity->world->collision_query_sphere_list(this, point, radius, tagToQueryFor);
	}



	void update() override
	{
		position = Vec2(entity->position.x + offset.x, entity->position.y + offset.y);
	}

	void render(Renderer* ren) override
	{
		//ren->draw_box(position, size, Vec3(0.1f, 0.1f, 1.0f));
		if (last_circle_query.second != 0)
			ren->draw_circle(last_circle_query.first, last_circle_query.second);
	}

};