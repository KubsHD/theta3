#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"


class Adult : public Enemy
{
public:
	Vec2 temp_pos;
	Entity* player;


	Adult() = default;

	Adult(Entity* player_ref)
	{
		health = 40;
		damage = 10;
		souls = 5;
		speed = 1.3f;

		temp = 30;

		player = player_ref;
	}


	void update() override
	{
		// Play a sound here or sth
		/*if (temp < 0) {

			temp = 30;
		}
		temp--;*/

		// Delayed
		//float delta_x = temp_pos.x - entity->position.x;
		//float delta_y = temp_pos.y - entity->position.y;

		// Standard
		float delta_x = player->position.x - entity->position.x;
		float delta_y = player->position.y - entity->position.y;

		facing_angle = atan2(delta_y, delta_x);

		// Movement 
		if (abs(delta_x) > 20 || abs(delta_y) > 20) {
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
		}

	}

	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};