#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"


class Policeman : public Enemy
{
public:
	Vec2 temp_pos;
	Entity* player;


	Policeman() = default;

	Policeman(Entity* player_ref)
	{
		health = 10;
		damage = 15;
		souls = 7;
		speed = 4.0f;

		temp = 90;

		player = player_ref;
	}


	void update() override
	{
		if (temp < 0) {
			temp_pos = player->position;
			temp = 90;
		}
		temp--;

		// Delayed
		float delta_x = temp_pos.x - entity->position.x;
		float delta_y = temp_pos.y - entity->position.y;

		// Standard
		//float delta_x = player->position.x - entity->position.x;
		//float delta_y = player->position.y - entity->position.y;

		facing_angle = atan2(delta_y, delta_x);

		// Movement 
		if (abs(delta_x) != 0 || abs(delta_y) != 0) {
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
		}

	}

	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};