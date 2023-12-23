#pragma once

#include "enemy.h"

#include <iostream>
#include "dmg_popup.h"
#include <iostream>
#include "utils/profiler.h"



void Enemy::flip_sprite()
{

	if (flip) {
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

	delta_x = player->pos_sprite_center.x - entity->position.x;
	delta_y = player->pos_sprite_center.y - entity->position.y;

	facing_angle = atan2(delta_y, delta_x);
	//std::cout << "facing angl: " << facing_angle << "\n";

	// flip?
	if (entity->position.x - target_pos.x > 0) {
		flip = 1;
	}
	else {
		flip = 0;
	}


	flip_sprite();

	if (state == EnemyState::IN_KNOCKBACK)
	{
		entity->position = glm::lerp(entity->position, target_knochback_position, 0.1f);

		if (glm::distance(entity->position, target_knochback_position) < 1)
			state = EnemyState::ATTACK;

		return;
	}
}


void Enemy::take_damage(float melee_damage, float knockback_rate)
{
	Factory::CreateDamagePopup(this->entity->world, entity->position, melee_damage);
	health -= melee_damage;
	// todo: knockback
	//Audio::play_one_shot(audio_damage_dealt);

	state = EnemyState::IN_KNOCKBACK;

	target_knochback_position = entity->position + Vec2( -cos(facing_angle) * 100 * knockback_rate, -sin(facing_angle) * 100 * knockback_rate);
	//std::cout << "kb: " << facing_angle << " | " << (Vec2(-cos(facing_angle) * 100 * knockback_rate, -sin(facing_angle) * 100 * knockback_rate)).x << " " << (Vec2(-cos(facing_angle) * 100 * knockback_rate, -sin(facing_angle) * 100 * knockback_rate)).y << "\n";

}



void Enemy::followPlayer()
{
	THETA_PROFILE;

	if (state == EnemyState::IN_KNOCKBACK)
		return;

	entity->position = glm::lerp(entity->position, target_pos, lerp_rate);

	if (currentPathPosition != path.end()-1 and (looper > 0)) {
		looper++;
		++currentPathPosition;

		target_pos = { currentPathPosition->x * 20 , currentPathPosition->y * 20};

		if (looper >= maxloops)
			looper = 0;
	}
	else {
		looper++;
		path = astar.findPath({ static_cast<int>(entity->position.x / 20), static_cast<int>(entity->position.y) / 20 },
			{ int(player->pos_sprite_center.x) / 20, int(player->pos_sprite_center.y) / 20 });
		std::reverse(path.begin(), path.end());
		currentPathPosition = path.begin();
	}
}
		//entity->position = glm::lerp(entity->position, target_pos, 1.0f);
