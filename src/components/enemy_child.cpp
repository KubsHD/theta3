#include "enemy_child.h"


Child::Child(Entity* player_ref)
{
	health = 10;
	damage = 15;
	souls = 7;
	speed = 3.0f;

	temp_pos = Vec2(0, 0);
	temp_val = 0;
	temp = 180;

	player = player_ref;
}


void Child::update()
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
	else if (abs(delta_x) + abs(delta_y) < 200)
	{
		entity->position.x -= cos(facing_angle) * speed;
		entity->position.y -= sin(facing_angle) * speed;
	}
	else if (abs(delta_x) + abs(delta_y) > 220)
	{
		entity->position.x += cos(facing_angle) * speed;
		entity->position.y += sin(facing_angle) * speed;
	}
	temp--;
}
