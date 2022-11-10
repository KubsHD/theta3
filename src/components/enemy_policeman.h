#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"


class Policeman : public Enemy
{
public:
	Vec2 temp_pos;
	Entity* player;
	bool running;
	float damage_gun;

	Policeman() = default;

	Policeman(Entity* player_ref)
	{
		health = 100;
		damage = 25;
		damage_gun = 10;
		souls = 7;
		speed = .7f;

		temp = 90;

		player = player_ref;
	}


	void update() override
	{
		//if (temp < 0) {
		//	// shoot here
		//	// bool running tells if he is shooting fast in safe position
		//} // or he is running away from player 
		//	// and shooting slower and with lower accuracy
		//temp--;

	

		// Standard
		float delta_x = player->position.x - entity->position.x;
		float delta_y = player->position.y - entity->position.y;

		facing_angle = atan2(delta_y, delta_x);

		
		// Movement 
		running = false;
		if (abs(delta_x) > 100 || abs(delta_y) > 100) {
			speed = 0.8f;
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
			running = true;
		}
		// dont get too close
		else if (abs(delta_x) < 30|| abs(delta_y) < 30) {
			speed = 2.5f; // uciekaja szybciej niz gonia jak irl lmao
			entity->position.x -= cos(facing_angle) * speed;
			entity->position.y -= sin(facing_angle) * speed;
			running = true;
		}
		// get info when in safe disctance


	}

	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};