/*****************************************************************//**
 * \file   player.h
 * \brief  player component with many necessary attributes like health, selected weapon etc.
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "core/input.h"




/// <summary>
/// class holding all the player attributes
/// </summary>
class Player : public Component
{
public:
	// Custom variables	
	float health, speed;
	int money;
	int kill_count;
	float damage_melee;
	Collider* collider;
	Vec2 pos_sprite_center;
	Vec2 player_offset;
	bool god_mode;
	float health_decay;
	int selected_weapon;
	int available_weapons;
	int weapon_cooldown;
	int enemies;

	Player();

	
	// Maintenance
	void init() override;
	void update() override;
	void render(Renderer* ren) override;
};