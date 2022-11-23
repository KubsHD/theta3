#include "enemy_policeman.h"


Policeman::Policeman(Entity* player_ref)
{
	health = 100;
	damage = 25;
	souls = 7;
	speed = .7f;

	damage_gun = 10;

	temp_val = 0;
	temp = 90; // cooldown

	player = player_ref;
}


void Policeman::update()
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
	if (abs(delta_x) + abs(delta_y) > 200) {
		speed = 0.8f;
		entity->position.x += cos(facing_angle) * speed;
		entity->position.y += sin(facing_angle) * speed;
		running = true;
	}
	// dont get too closel	
	else if (abs(delta_x) + abs(delta_y) < 180) {
		speed = 2.5f; // uciekaja szybciej niz gonia jak irl lmao
		entity->position.x -= cos(facing_angle) * speed;
		entity->position.y -= sin(facing_angle) * speed;
		running = true;
	}
}
