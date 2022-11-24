#include "enemy_bullet.h"


Bullet::Bullet(Entity* player_ref)
{
	souls = 0;
	speed = 1.8f;

	// set if player is able to destroy bullet mid-air;
	is_destructible = false;

	first_frame = true;

	player = player_ref;
}


void Bullet::update()
{
	if (first_frame == true)
	{
		temp_pos = player->position;
		entity->position = Vec2(100, 100);

		first_frame = false;

		float delta_x = temp_pos.x - entity->position.x;
		float delta_y = temp_pos.y - entity->position.y;

		facing_angle = atan2(delta_y, delta_x);
	}

	// Movement
	entity->position.x += cos(facing_angle) * speed;
	entity->position.y += sin(facing_angle) * speed;

	flip_sprite();
}
