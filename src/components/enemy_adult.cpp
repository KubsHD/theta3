#include "enemy_adult.h"

Adult::Adult(Entity* player_ref)
{
	health = 40;
	damage = 10;
	souls = 5;
	speed = 1.3f;


	temp_val = 0;
	temp = 30;

	player = player_ref;
}


void Adult::update()
{
	// Play a sound here or sth
	/*if (temp < 0) {

		temp = 30;
	}
	temp--;*/

	// Standard
	float delta_x = player->position.x - entity->position.x;
	float delta_y = player->position.y - entity->position.y;

	facing_angle = atan2(delta_y, delta_x);

	// Movement 
	if (abs(delta_x) + abs(delta_y) > 30) {
		entity->position.x += cos(facing_angle) * speed;
		entity->position.y += sin(facing_angle) * speed;
	}

	temp_val++;
	if (temp_val == 360)
		temp_val == 0;
}
