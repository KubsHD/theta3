#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <SDL_stdinc.h>


class Child : public Enemy
{
public:
	Entity* player;
	Vec2 temp_pos;
	float temp_val;
	float delta_x, delta_y;

	Child() = default;

	Child(Entity* player_ref)
	{
		health = 10;
		damage = 15;
		souls = 7;
		speed = 3.4f;


		temp_val = 0;
		temp = 180;

		player = player_ref;
	}


	void update() override
	{
		// Standard
		delta_x = player->position.x - entity->position.x;
		delta_y = player->position.y - entity->position.y;

		facing_angle = atan2(delta_y, delta_x);

		// Movement 
		if (temp < 0)
		{
			if (abs(delta_x) + abs(delta_y) > 20)
			{
				entity->position.x += cos(facing_angle) * speed;
				entity->position.y += sin(facing_angle) * speed;
				// melee attack with lolipop or spitting on player
			}
			else
			{
				temp = 180;
			}
		}
		else if (abs(delta_x) + abs(delta_y) > 400) {
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
			
		}
		// dont get too closel	
		else if (abs(delta_x) + abs(delta_y) < 395) {
			entity->position.x -= cos(facing_angle) * speed;
			entity->position.y -= sin(facing_angle) * speed;
		}
		temp--;

	}

	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};