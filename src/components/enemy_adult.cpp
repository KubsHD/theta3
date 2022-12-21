#include "enemy_adult.h"
#include "collider.h"


Adult::Adult(Player* player_ref) : Enemy(player_ref)
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

	audio_death = Asset::load_sound("data/audio/enemy_adult_death.mp3");
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

	this->entity->get<Animator>()->play_anim("adult_enemy_run");

	collider = entity->get<Collider>();
	// todo zmienic na rozmiar spritea
	collider->size = this->entity->get<Sprite>()->tex->size;
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
		if (!collider->check_sphere(Vec2(entity->position.x + collider->size.x/2 + cos(facing_angle) * collider->size.x/2,
				entity->position.y + collider->size.y/2 + sin(facing_angle) * collider->size.y/2), 2, CollisionTag::Enemy))
		{
			if (abs(delta_x) + abs(delta_y) > 30) {
				entity->position.x += cos(facing_angle) * speed;
				entity->position.y += sin(facing_angle) * speed;
			}
		}

		/*else if (delta_y > 0 && !collider->check_sphere(Vec2(entity->position.x + collider->size.x / 2, entity->position.y + collider->size.y / 2), 2, CollisionTag::Enemy))
		{
			entity->position.y += speed;
		}
		else
		{
			entity->position.y += speed;
		}*/


		// Damage to player
		//TODO: FIXLATER: IMPORTANT OPTIMIZATION!!!!!!!!!!!! CAN BE MERGED WITH MOVEMENT COLLIDER ABOVE
		if (collider->check_sphere(Vec2(entity->position.x + collider->size.x / 2 + cos(facing_angle) * collider->size.x / 2,
			entity->position.y + collider->size.y / 2 + sin(facing_angle) * collider->size.y / 2), 2, CollisionTag::Player))
		{
				this->entity->get<Animator>()->play_one_shot("adult_enemy_attack", [this](){});

		}


	// Animation
	this->entity->get<Sprite>()->enabled = false;
	}
}
