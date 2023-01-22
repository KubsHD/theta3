/*****************************************************************//**
 * \file   enemy_adult.h
 * \brief  component resposible for enemy type: Soldier
 *
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <iostream>


 /// <summary>
 /// class responsible for enemies stats and AI
 /// </summary>
class Soldier : public Enemy
{
public:
	// Custom variables
	Vec2 pos;
	Entity* player;
	bool running;
	float damage_gun, damage_grenade;

	// Constructors
	Soldier() = default;
	Soldier(Entity* player_ref);

	// Maintenance
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};