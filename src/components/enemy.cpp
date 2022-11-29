#include "enemy.h"

#include <iostream>

void Enemy::flip_sprite()
{

	if (facing_angle > (M_PI / 2) || facing_angle < -(M_PI / 2)) {
		this->entity->get<Animator>()->flip = true;
		this->entity->get<Sprite>()->flip = true;
	}
	else {
		this->entity->get<Animator>()->flip = false;
		this->entity->get<Sprite>()->flip = false;
	}
}

void Enemy::drop_loot()
{
	;
}

void Enemy::on_death()
{
	if (health <= 0 && is_dead == false)
	{
		is_dead = true;

		if (audio_death != NULL) {
			std::cout << entity->name << " - Zginal\n";
			Audio::play_one_shot(audio_death);
			
			drop_loot();
			// skasuj przeciwnika			
		}
	}
}
