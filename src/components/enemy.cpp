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

// Move to each enemy type separately
//void Enemy::on_death()
//{
//	if (health <= 0 && is_dead == false)
//	{
//		is_dead = true;
//
//		if (audio_death != NULL) {
//			std::cout << entity->name << " - Zginal\n" + std::to_string(entity->position.x)
//				+ " / " + std::to_string(entity->position.y);
//			
//			// play death sound
//			Audio::play_one_shot(audio_death);
//
//			// Death Loot Instantly added
//			player->health += this->souls;
//			player->money += this->money;
//			
//
//			// skasuj przeciwnika		
//			this->entity->world->remove(this->entity);
//		}
//	}
//}

void Enemy::handle_collision()
{

}

void Enemy::take_damage(float melee_damage, float knockback_rate)
{
	health -= melee_damage;
	// todo: knockback
	Audio::play_one_shot(audio_damage_dealt);
}
