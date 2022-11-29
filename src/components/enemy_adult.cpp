#include "enemy_adult.h"
#include "collider.h"


Adult::Adult(Entity* player_ref)
{
	health = 40;
	damage = 10;
	souls = 5;
	speed = 1.3f;

	temp_pos = Vec2(0, 0);
	temp_val = 0;
	temp = 30;



	player = player_ref;
}


void Adult::init()
{
	this->entity->get<Animator>()->play_anim("normal_human_move");
	auto col = entity->get<Collider>();
	col->on_collision_enter = [this](Entity* other) { can_walk = false; };
	col->on_collision_leave = [this](Entity* other) { can_walk = true; };
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
	if (can_walk)
	{ 
		if (abs(delta_x) + abs(delta_y) > 30) {
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
		}
	// Animation
	this->entity->get<Sprite>()->enabled = false;
	}

	flip_sprite();
}
