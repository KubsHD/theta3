#include "enemy_adult.h"
#include "collider.h"


Adult::Adult(Player* player_ref)
{
	health = 40;
	damage = 10;
	souls = 5;
	money = 3;

	speed = 1.1f;
	temp_pos = Vec2(0, 0);
	temp_val = 0;
	temp = 30;

	can_walk = true;

	audio_death = Audio::create_sound("data/audio/enemy_adult_death.mp3");

	// player reference
	player = player_ref;
 }


void Adult::init()
{
	Enemy::init();
	
	Vec2 rand_starting_pos;
	// 2 sides of the screen for x
	if (rand() % 2)
	{
		if (rand() % 2)
			rand_starting_pos.x = player->entity->position.x + rand() % 600;
		else
			rand_starting_pos.x = player->entity->position.x - rand() % 600;

		// 2 sides of the screen for y
		if (rand() % 2)
			rand_starting_pos.y = player->entity->position.y + rand() % 200 + 500;
		else
			rand_starting_pos.y = player->entity->position.y - rand() % 200 - 400;
	}
	else
	{
		if (rand() % 2)
			rand_starting_pos.x = player->entity->position.x + rand() % 200 + 800;
		else
			rand_starting_pos.x = player->entity->position.x - rand() % 200 - 700;

		// 2 sides of the screen for y
		if (rand() % 2)
			rand_starting_pos.y = player->entity->position.y + rand() % 400;
		else
			rand_starting_pos.y = player->entity->position.y - rand() % 400;
	}

	
	entity->position = rand_starting_pos;
	
	this->entity->get<Animator>()->play_anim("normal_human_move");	

	collider = entity->get<Collider>();
	// todo zmienic na rozmiar spritea
	collider->size = Vec2(32, 32);
	collider->tag = CollisionTag::Enemy;

}

void Adult::update()
{
	Enemy::update();

	//if (temp < 0) {
	//	// sztucznie zabijam
	//	temp = 60;
	//	health -= 15;
	//}
	//temp--;

	
	// Standard
	float delta_x = player->entity->position.x - entity->position.x;
	float delta_y = player->entity->position.y - entity->position.y;

	facing_angle = atan2(delta_y, delta_x);


	// Movement 
	if (can_walk)
	{ 
		if (!collider->check_sphere(entity->position, 1, CollisionTag::Enemy))
		{
			if (abs(delta_x) + abs(delta_y) > 30) {
				entity->position.x += cos(facing_angle) * speed;
				entity->position.y += sin(facing_angle) * speed;
			}
		}
	// Animation
	this->entity->get<Sprite>()->enabled = false;
	}
}
