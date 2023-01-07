#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <iostream>


class Player : public Component
{
public:
	// Custom variables
	float health, speed;
	int money;
	float damage_melee;
	Collider* collider;
	Vec2 pos_sprite_center;
	Vec2 player_offset;
	bool god_mode;
	float health_decay;
	int selected_weapon;
	int available_weapons;

	Player();

	
	// Maintenance
	void init() override;
	void update() override;
	void render(Renderer* ren) override;
};