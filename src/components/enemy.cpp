#pragma once

#include "enemy.h"

#include <iostream>
#include "dmg_popup.h"

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

	// Calculate A* path from the enemy's current position to the player's position
	AStar::CoordinateList path = astar.findPath({ static_cast<int>(entity->position.x), static_cast<int>(entity->position.y) },
		{ static_cast<int>(player->entity->position.x), static_cast<int>(player->entity->position.y) });

	// Move the enemy along the path (you may need to adjust the movement speed)
	if (!path.empty())
	{
		AStar::Vec2i nextTile = path.back();
		float targetX = static_cast<float>(nextTile.x);
		float targetY = static_cast<float>(nextTile.y);

		// Move towards the next tile in the path
		entity->position.x += (targetX - entity->position.x) * speed;
		entity->position.y += (targetY - entity->position.y) * speed;
	}
}
