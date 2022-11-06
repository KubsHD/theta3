#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"


class Adult : public Enemy
{
public:
	float facing_angle, temp;
	Vec2 temp_pos;
	Entity* player;


	Adult() = default;

	Adult(Entity* player_ref)
	{
		health = 40;
		damage = 10;
		souls = 5;
		speed = 1.4f;

		
		player = player_ref;
	}

	
	void update() override
	{
		if (health < 0) {
			//log_info("player pos: %f, %f\n", player->position.x, player->position.y);
			//log_info("entity1 pos: %f, %f\n", entity->position.x, entity->position.y);
			//log_info("facing_angle: %f\n", facing_angle * 180 / M_PI);
			//log_info("cos: %f\n\n", cos(facing_angle));

			temp_pos = player->position;

			health = 30;
		}
		health--;

		// Delayed
		float delta_x = temp_pos.x - entity->position.x;
		float delta_y = temp_pos.y - entity->position.y;

		// Standard
		/*float delta_x = player->position.x - entity->position.x;
		float delta_y = player->position.y - entity->position.y;*/
		
		facing_angle = atan2( delta_y, delta_x);

		
		
		// Movement 
		if ( abs(delta_x) > 20 || abs(delta_y) > 20) {
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
		}
	
		

	}

	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};