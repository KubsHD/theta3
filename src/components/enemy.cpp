#pragma once

#include "enemy.h"

#include <iostream>
#include "dmg_popup.h"
#include "core/input.h"
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

void Enemy::update()
{
	flip_sprite();

	if (state == EnemyState::IN_KNOCKBACK)
	{
		entity->position = glm::lerp(entity->position, target_knochback_position, 0.1f);

		if (glm::distance(entity->position, target_knochback_position) < 1)
			state = EnemyState::ATTACK;

		return;
	}
}


void Enemy::take_damage(float melee_damage, float knockback_rate, float facing_angle)
{
	Factory::CreateDamagePopup(this->entity->world, entity->position, melee_damage);
	health -= melee_damage;
	// todo: knockback
	//Audio::play_one_shot(audio_damage_dealt);

	state = EnemyState::IN_KNOCKBACK;

	target_knochback_position = entity->position + Vec2( -cos(facing_angle) * 100 * knockback_rate, -sin(facing_angle) * 100 * knockback_rate);
}



void Enemy::followPlayer()
{
	if (state == EnemyState::IN_KNOCKBACK)
		return;



	entity->position = glm::lerp(entity->position, target_pos, 0.04f);

	if (currentPathPosition != path.end()-1 and (looper > 0)) {
		looper++;
		++currentPathPosition;
		std::cout << "Current position: " << currentPathPosition->x << " " << currentPathPosition->y << "\n";

		target_pos = { currentPathPosition->x * 20 , currentPathPosition->y * 20};

		std::cout << looper << "- L1" << std::endl;

		if (looper == maxloops)
			looper = 0;
	}
	else {
		looper++;
		std::cout << looper << "- L2" << std::endl;
		std::cout << "Path not found.\n";
		path = astar.findPath({ static_cast<int>(entity->position.x / 20), static_cast<int>(entity->position.y) / 20 },
			{ int(player->pos_sprite_center.x) / 20, int(player->pos_sprite_center.y) / 20 });
		std::reverse(path.begin(), path.end());

		currentPathPosition = path.begin();
		
	}
}
		//entity->position = glm::lerp(entity->position, target_pos, 1.0f);
