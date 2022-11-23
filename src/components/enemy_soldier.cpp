#include "enemy_soldier.h"


Soldier::Soldier(Entity* player_ref)
{
	health = 100;
	damage = 25;
	damage_gun = 10;
	souls = 7;
	speed = .7f;

	temp = 90;
	player = player_ref;
}


void Soldier::update()
{
	// full accuracy all the time
	if (temp < 0) {
		if (running == false)
			;//throw granade
	}
	temp--;

	// Standard
	float delta_x = player->position.x - entity->position.x;
	float delta_y = player->position.y - entity->position.y;

	facing_angle = atan2(delta_y, delta_x);

	// Movement 
	if (abs(delta_x) + abs(delta_y) > 290) {
		speed = 2.1f;
		entity->position.x += cos(facing_angle) * speed;
		entity->position.y += sin(facing_angle) * speed;
		running = true;
	}
	// dont get too close
	else if (abs(delta_x) + abs(delta_y) < 250) {
		speed = 2.1f;
		entity->position.x -= cos(facing_angle) * speed;
		entity->position.y -= sin(facing_angle) * speed;
		running = true;
	}
	// get info when in safe disctance
	else
		// throw granade
		running = false;
}
