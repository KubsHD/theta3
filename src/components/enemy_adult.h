#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <SDL_stdinc.h>


class Adult : public Enemy
{
public:
	Vec2 temp_pos;
	Entity* player;
	int temp_val;


	Adult() = default;

	Adult(Entity* player_ref)
	{
		health = 40;
		damage = 10;
		souls = 5;
		speed = 1.3f;


		temp_val = 0;
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

		// Standard
	/*	float delta_x = player->position.x - entity->position.x;
		float delta_y = player->position.y - entity->position.y;

		facing_angle = atan2(delta_y, delta_x);*/

		//// Movement 
		//if (abs(delta_x) + abs(delta_y) > 30) {
		//	entity->position.x += cos(facing_angle) * speed;
		//	entity->position.y += sin(facing_angle) * speed;
		//}

		// Run circles / WIP
		entity->position.x += cos(temp_val * M_PI / 180) * speed;
		entity->position.y += sin(temp_val * M_PI / 180) * speed;

		temp_val++;
		if (temp_val == 360)
			temp_val == 0;

	}

	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};